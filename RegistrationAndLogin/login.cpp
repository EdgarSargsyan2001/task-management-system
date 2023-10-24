#include <QMessageBox>
#include <QStyle>
#include <QSettings>

#include "login.h"
#include "ui_login.h"

#include "hellpers/hellpers.h"
#include "style/line_edit.h"
#include "style/button.h"


#include "reset_password.h"
#include "email_verification.h"
#include "email_input.h"
#include "register.h"
#include "Languages/change_language.h"
#include "Data/task/taskData.h"

login::login(QTranslator*p,QWidget *parent) :
    QDialog(parent),
    m_translator(p),
    ui(new Ui::login)
{
    ui->setupUi(this);

    ui->email->setStyleSheet(input_style);
    ui->password->setStyleSheet(input_style);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);//disable resizing

    connect_database();
//    ui->toolButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));

    ui->login_btn->setStyleSheet(button_style + button_style_hover + button_style_pressed);
}

login::~login()
{
    m_db.close();
    delete ui;
}

bool login::connect_database(){

    QSettings settings(".env", QSettings::IniFormat);
    QString DATABASE_NAME = settings.value("DATABASE_NAME").toString();
    QString HOST = settings.value("HOST").toString();
    QString PASSWORD = settings.value("PASSWORD").toString();
    QString USER_NAME = settings.value("USER_NAME").toString();

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(HOST);
    m_db.setUserName(USER_NAME);
    m_db.setDatabaseName(DATABASE_NAME);
    m_db.setPassword(PASSWORD);

    if(!m_db.open()){
        QMessageBox::warning(this,tr("database") , tr("database not open"));
        exit(0);
    }else{
        qDebug("database open");

        QSqlQuery query;
        query.prepare("CREATE TABLE users ("

                      "id INT AUTO_INCREMENT PRIMARY KEY,"
                      "name VARCHAR(30) NOT NULL,"
                      "email VARCHAR(255) NOT NULL,"
                      "password VARCHAR(255) NOT NULL,"
                      "role INT NOT NULL DEFAULT 0 "

                      ")");

        if (query.exec()) {

            qDebug() << "users Table created successfully!";
        } else {
            //            qDebug() << "Table creation failed:";
        }

        // Create the Tasks table with a foreign key reference to Users
        if (query.exec("CREATE TABLE Tasks ("

                       " id INT AUTO_INCREMENT PRIMARY KEY,"
                       " user_id INTEGER NOT NULL,"
                       " name VARCHAR(60) NOT NULL,"
                       " description TEXT NOT NULL,"
                       " date DATE NOT NULL,"
                       " FOREIGN KEY (user_id) REFERENCES users(id)"

                       ")")
            ) {
            qDebug() << "Tasks table created successfully.";
        } else {
            //            qDebug() << "Error creating Tasks table: " ;
        }
    }

    return true;
}

void login::update_ui(){

    ui->retranslateUi(this);
}


void login::on_register_btn_clicked()
{
    email_input emailInput{email_has_been_used_in_db::email_used,this};
    email_verification emailV(this);

    Register reg_dialog(this);
    QObject::connect(&emailV,email_verification::verificationSuccessful,&reg_dialog,Register::set_verificationEmail);
    QObject::connect(&emailV,email_verification::verificationSuccessful,&reg_dialog,Register::exec);

    QObject::connect(&emailInput,email_input::pass_email,&emailV,email_verification::send_code);
    QObject::connect(&emailInput,email_input::pass_email,&emailV,email_verification::exec);

    emailInput.exec();

}
void login::on_login_btn_clicked()
{
    QString email = ui->email->text().trimmed();
    QString password = ui->password->text();

    if(!Hellpers::is_valid_email(email)){

        QMessageBox::warning(this,tr("Invalid Email") ,tr("Invalid Email !!!"));
        return;
    }

    if(!Hellpers::is_valid_password(password)){

        QMessageBox::warning(this,tr("Invalid password"),tr("Invalid password !!!"));
        ui->password->setText("");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE email = :_email");
    query.bindValue(":_email",email);

    if(query.exec()){
        if(query.next()){

            QString password_in_db =  query.value(user_data_in_db::password).toString();

            if(password_in_db == Hellpers::hash_password( password)){
                qDebug()<<"login is successfully";
                ui->password->setText("");
                ui->email->setText("");

                UserData * pd = new UserData(
                        query.value(user_data_in_db::u_id).toInt(),
                        query.value(user_data_in_db::u_name).toString(),
                        email
                    );

                QVector<taskData*> tasks =  Hellpers::get_user_tasks_form_db(pd->get_id());
                for(int i = 0;i < tasks.size(); ++i){
                    pd->set_task(tasks[i]);
                }

                emit loginSuccess(pd);
                hide();

            }else{
                ui->password->setText("");
                ui->password->setFocus();
                QMessageBox::warning(this,tr("Invalid password") ,tr("Invalid password !!!"));
                return;
            }

        }else{
            QMessageBox::warning(this,tr("Invalid Email") ,tr("This email is not registered !!!"));
            return ;
        }
    }else{
        qDebug()<<"query not work";
    }
}

void login::on_email_textChanged(const QString &arg1)
{
    if(Hellpers::is_valid_email(arg1)){
        ui->email->setStyleSheet(input_style_valid);
    }else{
        ui->email->setStyleSheet(input_style);
    }
}

void login::on_password_textChanged(const QString &arg1)
{
    if( Hellpers::is_valid_password(arg1)){
        ui->password->setStyleSheet(input_style_valid);
    }else{
        ui->password->setStyleSheet(input_style);
    }
}

void login::on_forget_pass_btn_clicked()
{

    email_input emailInput{email_has_been_used_in_db::email_did_not_use,this};
    email_verification emailV(this);

    reset_password reset_pass(this);
    QObject::connect(&emailV,email_verification::verificationSuccessful,&reset_pass,reset_password::set_verificationEmail);
    QObject::connect(&emailV,email_verification::verificationSuccessful,&reset_pass,reset_password::exec);

    QObject::connect(&emailInput,email_input::pass_email,&emailV,email_verification::send_code);
    QObject::connect(&emailInput,email_input::pass_email,&emailV,email_verification::exec);

    emailInput.exec();

}


void login::on_toolButton_clicked()
{
    change_language l(m_translator);

    connect(&l,change_language::change_successful,this,update_ui);

    l.exec();
}

