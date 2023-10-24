#ifndef HELLPERS_H
#define HELLPERS_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QRegularExpression>
#include <QCryptographicHash>
#include <QVector>
#include "Data/task/taskData.h"

enum user_data_in_db{
    u_id,
    u_name,
    email,
    password,
    role
};

enum task_data_in_db{
    t_id,
    user_id,
    t_name,
    desc,
    date
};

class Hellpers
{
public:

    static const QString hash_password(const QString& password){
        QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha3_256).toHex());

        return hashedPassword;
    }

    static bool is_valid_name(const QString& name){
        if(name.length() < 3 || name.length() > 28 || name.contains(' ')){
            return false;
        }
        return true;
    }

    static bool is_valid_email(const QString& email){

        const QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return emailRegex.match(email).hasMatch();
    }
    static bool is_email_in_db(const QString& _email){
        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE email = :_email");
        query.bindValue(":_email",_email);

        if(query.exec()){
           if (query.next()) {

               qDebug()<<"email found in database\n";
               return true;
           }
        }else{
           qDebug()<<"query not work";

        }
        return false;
    }

    static bool is_valid_password(const QString& str){

        if(str.length() < 8){
           return false;
        }
        return true;
    }

    static QVector<taskData*> get_user_tasks_form_db(int user_id){
        QVector<taskData*> v;
        QSqlQuery query;

        query.prepare("SELECT * FROM Tasks WHERE user_id = :user_id");
        query.bindValue(":user_id",user_id);

        if (query.exec()) {
           while (query.next()) {

               v.push_back(new taskData(

                   query.value(task_data_in_db::t_id).toInt(),
                   query.value(task_data_in_db::t_name).toString(),
                   query.value(task_data_in_db::desc).toString(),
                   query.value(task_data_in_db::date).toDate()

                   ));
           }

        } else {
           qDebug() << "Error retrieving tasks: ";
        }

        return std::move(v);
    }

    static taskData get_last_task_from_db(int user_id){
        QSqlQuery query;

        query.prepare("SELECT * FROM Tasks WHERE user_id = :user_id ORDER BY id DESC LIMIT 1");
        query.bindValue(":user_id",user_id);

        if (query.exec()) {

           if(query.next()){

               return taskData(

                   query.value(task_data_in_db::t_id).toInt(),
                   query.value(task_data_in_db::t_name).toString(),
                   query.value(task_data_in_db::desc).toString(),
                   query.value(task_data_in_db::date).toDate()

                   );
           }else{
               qDebug()<<"last task not found";
           }
        }
    }

public:
    Helpers() = delete;
};

#endif // HELLPERS_H
