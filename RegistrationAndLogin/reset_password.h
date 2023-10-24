#ifndef RESET_PASSWORD_H
#define RESET_PASSWORD_H

#include <QDialog>

namespace Ui {
class reset_password;
}

class reset_password : public QDialog
{
    Q_OBJECT

public:
    explicit reset_password(QWidget *parent = nullptr);
    ~reset_password();

private slots:
    void on_reg_btn_clicked();
    void on_password_textChanged(const QString &arg1);
    void on_repeat_password_textChanged(const QString &arg1);

public slots:
    void set_verificationEmail(const QString& email);

private:
    Ui::reset_password *ui;
    QString m_verificationEmail;
};

#endif // RESET_PASSWORD_H
