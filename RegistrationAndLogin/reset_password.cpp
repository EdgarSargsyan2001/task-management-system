#include <QMessageBox>

#include "reset_password.h"
#include "ui_reset_password.h"

#include "style/line_edit.h"
#include "hellpers/hellpers.h"

reset_password::reset_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reset_password)
{
    ui->setupUi(this);
    ui->password->setStyleSheet(input_style);
    ui->repeat_password->setStyleSheet(input_style);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);//disable resizing

}

reset_password::~reset_password()
{
    delete ui;
}

void reset_password::set_verificationEmail(const QString& email){
    m_verificationEmail = email;
}

void reset_password::on_reg_btn_clicked()
{
    QString password = ui->password->text();
    QString repeat_password = ui->repeat_password->text();

    if(password != repeat_password){

        QMessageBox::warning(this, tr("Invalid password"),tr("password and repeat password isn't same !!!"));
        ui->password->setText("");
        ui->repeat_password->setText("");
        ui->password->setFocus();
        return ;
    }

    if(!Hellpers::is_valid_password((password))){
        QMessageBox::warning(this,tr("Invalid password"),tr("Invalid password !!!"));
        return ;
    }

    QSqlQuery query;
    query.prepare("UPDATE users SET password = :password WHERE email = :email");

    query.bindValue(":email",m_verificationEmail);
    query.bindValue(":password", Hellpers::hash_password( password));

    if(query.exec()){
        this->close();
        QMessageBox::information(this,tr("reset password"),tr("reset password successfully "));
    }else{
        qDebug() << "reset password failed query not work ";
    }
}

void reset_password::on_password_textChanged(const QString &arg1)
{
    if( Hellpers::is_valid_password(arg1)){
        ui->password->setStyleSheet(input_style_valid);
    }else{
        ui->password->setStyleSheet(input_style);
    }
}

void reset_password::on_repeat_password_textChanged(const QString &arg1)
{
    if( Hellpers::is_valid_password(arg1)){
        ui->repeat_password->setStyleSheet(input_style_valid);
    }else{
        ui->repeat_password->setStyleSheet(input_style);
    }
}
