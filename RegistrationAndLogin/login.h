#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "Data/user/userdata.h"
#include <QTranslator>
#include <QSqlDatabase>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QTranslator*,QWidget *parent = nullptr);
    ~login();

private:
    bool connect_database();

private slots:
    void on_register_btn_clicked();

    void on_login_btn_clicked();

    void on_email_textChanged(const QString &arg1);

    void on_password_textChanged(const QString &arg1);

    void on_forget_pass_btn_clicked();

    void on_toolButton_clicked();

public slots:
    void update_ui();

signals:
    void loginSuccess(UserData*p);

private:
    Ui::login *ui;
    QSqlDatabase m_db;
    QTranslator *m_translator = nullptr;
};

#endif // LOGIN_H
