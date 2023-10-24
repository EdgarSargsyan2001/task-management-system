#include "createtask.h"
#include "style/button.h"
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include "hellpers/hellpers.h"

createTask::createTask(const UserData* const uD,QWidget *parent) :
    Task(parent),
    m_userData(uD)
{
    create_button->setStyleSheet(button_style + button_style_hover + button_style_pressed);
    create_button->setText(" Create ");
    date_edit->setDate(QDate::currentDate());

    connect(create_button,QPushButton::clicked,this,create_button_clicked);
}

void createTask::create_button_clicked(){

    QString name = name_edit->text();
    if(name.isEmpty()){
        QMessageBox::warning(this,"name","Name is empty!!!");
        return;
    }

    QString desc = desc_edit->toPlainText();
    if(desc.isEmpty()){
        QMessageBox::warning(this,"desc","desc is empty!!!");
        return;
    }

    QDate date = date_edit->date();
    QSqlQuery query;

    query.prepare("INSERT INTO Tasks (user_id,name,description,date) VALUES (:user_id, :name, :description, :date)");
    query.bindValue(":user_id", m_userData->get_id());
    query.bindValue(":name", name);
    query.bindValue(":description", desc);
    query.bindValue(":date", date);

    if (query.exec()) {

        emit Task_added_successfully(Hellpers::get_last_task_from_db(m_userData->get_id()));
        qDebug() << "Task added successfully.";

    } else {
        qDebug() << "Error adding Task: " ;
    }

    close();
}
