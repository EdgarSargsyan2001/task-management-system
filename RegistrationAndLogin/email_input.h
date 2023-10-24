#ifndef EMAIL_INPUT_H
#define EMAIL_INPUT_H

#include <QDialog>

enum class email_has_been_used_in_db{
    email_used,
    email_did_not_use
};

namespace Ui {
class email_input;
}

class email_input : public QDialog
{
    Q_OBJECT

public:
    explicit email_input(email_has_been_used_in_db r,QWidget *parent = nullptr);
    ~email_input();
signals:
    void pass_email(const QString& e);

private slots:
    void on_send_mess_btn_clicked();

    void on_email_textChanged(const QString &arg1);

private:
    Ui::email_input *ui;
    email_has_been_used_in_db res;

};

#endif // EMAIL_INPUT_H
