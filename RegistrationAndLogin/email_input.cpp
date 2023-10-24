#include <QMessageBox>

#include "email_input.h"
#include "ui_email_input.h"

#include "hellpers/hellpers.h"
#include "style/line_edit.h"

email_input::email_input(email_has_been_used_in_db r,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::email_input),
    res(r)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);//disable resizing
    ui->retranslateUi(this);

}

email_input::~email_input()
{
    delete ui;
}

void email_input::on_send_mess_btn_clicked()
{

    QString email = ui->email->text().trimmed();

    if(!Hellpers::is_valid_email(email)){
        QMessageBox::warning(this,tr("Invalid Email") ,tr("Invalid Email !!!") );
        ui->email->setFocus();
        return ;
    }
    switch (res) {
    case email_has_been_used_in_db::email_used:
        if(Hellpers::is_email_in_db(email)){
            QMessageBox::warning(this,tr("Invalid Email") ,tr("That email is already in use !!!"));
            ui->email->setFocus();
            return ;
        }
        break;

    case email_has_been_used_in_db::email_did_not_use:
        if(!Hellpers::is_email_in_db(email)){
            QMessageBox::warning(this, tr("Invalid Email"),tr("That email isn't registered !!!"));
            ui->email->setFocus();
            return ;
        }
        break;
    }
    close();
    emit pass_email(email);
}

void email_input::on_email_textChanged(const QString &arg1)
{
    if( Hellpers::is_valid_email(arg1)){
        ui->email->setStyleSheet(input_style_valid);
    }else{
        ui->email->setStyleSheet(input_style);
    }
}

