#ifndef email_verification_H
#define email_verification_H

#include <QDialog>
class SmtpClient; //forward declaration

namespace Ui {
    class mail_verification;
}

class email_verification : public QDialog
{
    Q_OBJECT

public:
    explicit email_verification(QWidget *parent = nullptr);
    ~email_verification();
    void set_email(const QString& e){
        m_email = e;
    }

public slots:
    void send_code(QString e);

signals:
    void verificationSuccessful(const QString &);

private slots:
    void on_submit_btn_clicked();

private:
    QString generateVerificationCode();

private:
    Ui::mail_verification *ui;
    SmtpClient* m_smtp;
    QString m_genCode ;
    QString m_email ;

};

#endif // email_verification_H
