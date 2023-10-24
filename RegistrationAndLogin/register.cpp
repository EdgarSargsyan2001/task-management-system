#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "register.h"
#include "ui_register.h"

#include "hellpers/hellpers.h"
#include "style/line_edit.h"
#include "style/button.h"

#include "email_verification.h"


Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    ui->name->setStyleSheet(input_style);
    ui->password->setStyleSheet(input_style);
    ui->repeat_password->setStyleSheet(input_style);
    ui->reg_btn->setStyleSheet(button_style + button_style_hover + button_style_pressed);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);//disable resizing
}

Register::~Register()
{
    delete ui;
}
void Register::set_verificationEmail(const QString& email){
    m_verificationEmail = email;
}

bool Register::on_reg_btn_clicked()
{
    QString name = ui->name->text();
    QString password = ui->password->text();
    QString repeat_password = ui->repeat_password->text();

    if(!Hellpers::is_valid_name(name)){
        QMessageBox::warning(this,tr( "Invalid Name"),tr("Name is empty !!!") );
        return false;
    }
    if(password != repeat_password){

       QMessageBox::warning(this,tr( "Invalid password"),tr("password and repeat password isn't same !!!"));
        ui->password->setText("");
        ui->repeat_password->setText("");
        ui->password->setFocus();
        return false;
    }

    if(!Hellpers::is_valid_password((password))){
        QMessageBox::warning(this,tr("Invalid password") ,tr("Invalid password !!!"));
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO "
                     "users (name,email,password) "
                     "VALUES (:name,:email,:password)"
                  );

    query.bindValue(":name",name);
    query.bindValue(":email",m_verificationEmail);
    query.bindValue(":password",Hellpers::hash_password( password));

    if(query.exec()){
        qDebug() << "user regiseter successfully";
        this->close();
        QMessageBox::information(this,tr("registered"),tr("you have successfully registered "));
    }else{
        qDebug() << "user regiseter failed query not work ";
    }

    return true;
}

void Register::on_name_textChanged(const QString &arg1)
{
    if( Hellpers::is_valid_name(arg1)){
        ui->name->setStyleSheet(input_style_valid);
    }else{
        ui->name->setStyleSheet(input_style);
    }
}


void Register::on_password_textChanged(const QString &arg1)
{
    if( Hellpers::is_valid_password(arg1)){
        ui->password->setStyleSheet(input_style_valid);
    }else{
        ui->password->setStyleSheet(input_style);
    }
}

void Register::on_repeat_password_textChanged(const QString &arg1)
{
    if( Hellpers::is_valid_password(arg1)){
        ui->repeat_password->setStyleSheet(input_style_valid);
    }else{
        ui->repeat_password->setStyleSheet(input_style);
    }
}

