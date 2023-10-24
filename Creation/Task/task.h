#ifndef TASK_H
#define TASK_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QPushButton>
#include "Data/task/taskData.h"

namespace Ui {
class Task;
}

class Task : public QDialog
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();

signals:
    void Task_added_successfully(taskData);
    void Task_save_successfully(taskData);

protected:
    QLineEdit *name_edit;
    QTextEdit *desc_edit;
    QDateEdit *date_edit;
    QPushButton *create_button;

private:
    Ui::Task *ui;
};

#endif // TASK_H
