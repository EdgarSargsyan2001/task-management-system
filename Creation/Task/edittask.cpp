#include "edittask.h"
#include "style/button.h"

editTask::editTask(const taskData* tD,QWidget *parent )
    : Task(parent)
{
    name_edit->setText(tD->get_name());
    desc_edit->setText(tD->get_description());
    date_edit->setDate(tD->get_date());

    create_button->setStyleSheet(button_style + button_style_hover + button_style_pressed);
    create_button->setText(" Save ");

    connect(create_button,QPushButton::clicked,this,button_clicked);

}

void editTask::button_clicked(){

}

