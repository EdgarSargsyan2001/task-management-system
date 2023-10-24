#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QString>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Data/user/userdata.h"
#include "RegistrationAndLogin/reset_password.h"
#include "RegistrationAndLogin/email_verification.h"
#include "Languages/change_language.h"
#include "Creation/Task/createtask.h"
#include "Creation/Task/edittask.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>

MainWindow::MainWindow( QTranslator*p,UserData& ud, QWidget *parent)
    : QMainWindow(parent),
    m_translator(p),
    m_user_data(ud),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->name_label->setText(m_user_data.get_email());

    show_data();

}

MainWindow::~MainWindow()
{
    delete &m_user_data;
    delete ui;
}

void MainWindow::update_ui(){
    ui->retranslateUi(this);
}

void MainWindow::show_data(){

    QVector<const taskData* > tasks = m_user_data.get_tasks();

    for(int i = 0; i< tasks.size(); ++i){
        add_task_ui(tasks[i]);
    }
}

void MainWindow::add_task_ui(const taskData* t){

    QGroupBox * groupBox  = new QGroupBox();
    groupBox->setTitle(t->get_name());

    QHBoxLayout * Hlayout = new QHBoxLayout();

    QPushButton *deleteBtn = new QPushButton("Delete",this);
    QPushButton *editBtn = new QPushButton("Edit",this);

    connect(deleteBtn,QPushButton::clicked,this,[this,t,groupBox](){
        QSqlQuery deleteQuery;

        deleteQuery.prepare("DELETE FROM Tasks WHERE id = :taskId AND user_id = :userId");
        deleteQuery.bindValue(":taskId", t->get_id());
        deleteQuery.bindValue(":userId", m_user_data.get_id());

        if (deleteQuery.exec()) {
            int rowsAffected = deleteQuery.numRowsAffected();
            if (rowsAffected > 0) {

                this->ui->statusBar->showMessage("Task deleted successfully",3000);
            } else {
                qDebug() << "No matching task found for deletion";
            }
        }

        delete groupBox;

    });
    connect(editBtn,QPushButton::clicked,this,[this,t](){

        editTask editT(t);

        editT.exec();

        QPushButton* btn = (QPushButton*)sender();
        qDebug()<<"edit";
    });

    Hlayout->addWidget(deleteBtn);
    Hlayout->addWidget(editBtn);

    groupBox->setLayout(Hlayout);
    ui->verticalLayout->addWidget(groupBox);
}

void MainWindow::on_actionlog_out_triggered()
{
    qDebug()<<"user log out;";

    emit log_out();
}

void MainWindow::on_actionSecurity_triggered()
{
    email_verification emailV(this);
    emailV.send_code(m_user_data.get_email());

    reset_password reset_pass(this);
    reset_pass.set_verificationEmail(m_user_data.get_email());

    QObject::connect(&emailV,email_verification::verificationSuccessful,&reset_pass,reset_password::exec);

    emailV.exec();
}

void MainWindow::on_actionlanguage_triggered()
{
    change_language l(m_translator);

    connect(&l,change_language::change_successful,this,update_ui);
    connect(&l,change_language::change_successful,this,[this](){emit changeLanguage();});

    l.exec();
}

void MainWindow::on_pushButton_clicked()
{
    createTask t(&m_user_data,this);
    connect(&t,createTask::Task_added_successfully,this,[this](taskData lastTask){
        this->ui->statusBar->showMessage("Task added successfully.",3000);

        taskData* newTask = new taskData(lastTask);
        this->m_user_data.set_task(newTask);
        this->add_task_ui(newTask);
    });
    t.exec();
}


