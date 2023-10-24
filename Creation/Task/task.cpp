#include "task.h"
#include "ui_task.h"

Task::Task(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    name_edit = ui->name_edit;
    desc_edit = ui->desc_edit;
    date_edit = ui->date_Edit;
    create_button = ui->create_button;

}

Task::~Task()
{
    delete ui;
}
