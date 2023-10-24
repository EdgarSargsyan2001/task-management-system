#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    bool on_reg_btn_clicked();
    void on_name_textChanged(const QString &arg1);
    void on_password_textChanged(const QString &arg1);
    void on_repeat_password_textChanged(const QString &arg1);

public slots:
    void set_verificationEmail(const QString& email);

private:
    Ui::Register *ui;
    QString m_verificationEmail;
};

#endif // REGISTER_H
