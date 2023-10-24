#ifndef CHANGE_LANGUAGE_H
#define CHANGE_LANGUAGE_H

#include <QDialog>
#include <QTranslator>

namespace Ui {
class change_language;
}

class change_language : public QDialog
{
    Q_OBJECT

public:
    explicit change_language(QTranslator*,QWidget *parent = nullptr);
    ~change_language();

private slots:
    void on_comboBox_textActivated(const QString &arg1);

signals:
    void change_successful();

public:
    bool is_change_successful(){
        return is_change;
    }

private:
    Ui::change_language *ui;
    QTranslator* m_translator = nullptr;
    bool is_change = false;
};

#endif // CHANGE_LANGUAGE_H
