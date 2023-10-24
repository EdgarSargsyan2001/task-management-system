
//Task::Task(const UserData* const userData,QWidget *parent) :
//    QDialog(parent),
//    m_userData(userData),
//    ui(new Ui::Task)
//{
//    ui->setupUi(this);
//    ui->pushButton->setStyleSheet(button_style + button_style_hover + button_style_pressed);
//    ui->date_Edit->setDate(QDate::currentDate());
//}

//Task::~Task()
//{
//    delete ui;
//}

//void Task::on_pushButton_clicked()
//{
//    QString name = ui->name_edit->text();
//    if(name.isEmpty()){
//        QMessageBox::warning(this,"name","Name is empty!!!");
//        return;
//    }

//    QString desc = ui->desc_edit->toPlainText();
//    if(desc.isEmpty()){
//        QMessageBox::warning(this,"desc","desc is empty!!!");
//        return;
//    }

//    QDate date = ui->date_Edit->date();
//    QSqlQuery query;

//    query.prepare("INSERT INTO Tasks (user_id,name,description,date) VALUES (:user_id, :name, :description, :date)");
//    query.bindValue(":user_id", m_userData->get_id());
//    query.bindValue(":name", name);
//    query.bindValue(":description", desc);
//    query.bindValue(":date", date);


//    if (query.exec()) {

//        emit Task_added_successfully(Hellpers::get_last_Task_from_db(m_userData->get_id()));
//        qDebug() << "Task added successfully.";

//    } else {
//        qDebug() << "Error adding Task: " ;
//    }

//    close();
//}

