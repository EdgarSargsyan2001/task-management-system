#include <QMessageBox>
#include <QRandomGenerator>
#include <QSettings>

#include "email_verification.h"
#include "ui_email_verification.h"

#include "SMTP_Socket/smtp.h"
#include "text/text.h"

email_verification::email_verification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mail_verification)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);//disable resizing

    QSettings settings(".env", QSettings::IniFormat);

    QString SMTP_HOST = settings.value("SMTP_HOST").toString();
    int SMTP_PORT = settings.value("SMTP_PORT").toInt();
    QString SMTP_USERNAME = settings.value("SMTP_USERNAME").toString();
    QString SMTP_PASSWORD = settings.value("SMTP_PASSWORD").toString();

    m_smtp = new SmtpClient(SMTP_HOST,SMTP_PORT,SMTP_USERNAME,SMTP_PASSWORD);
}

email_verification::~email_verification()
{
    delete m_smtp;
    delete ui;
}

void email_verification::send_code(QString email)
{
    set_email(email);
    ui->label_email->setText(email);

    QSettings settings(".env", QSettings::IniFormat);
    QString SMTP_SENDER = settings.value("SMTP_SENDER").toString();

    m_genCode = generateVerificationCode();
    m_smtp->sendEmail(SMTP_SENDER,email,"Code Verification",Text::message + m_genCode);
}

void email_verification::on_submit_btn_clicked()
{
    QString code = ui->code->text().trimmed();

    if(code == m_genCode){
        close();
        emit verificationSuccessful(m_email);
    }
    else{
        QMessageBox::warning(this, tr("Invalid Code"),tr("Invalid Code !!!"));
        ui->code->setText("");
    }
}

QString email_verification::generateVerificationCode(){

    QString newCode;
    for(int i = 0;i < 6;++i){
        newCode += QString::number( QRandomGenerator::global()->bounded(0, 9));
    }
    qDebug()<<"email_verification line 66 :" <<newCode;
    return newCode;
}
