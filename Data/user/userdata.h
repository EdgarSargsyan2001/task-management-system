#ifndef USERDATA_H
#define USERDATA_H
#include <QString>
#include <QVector>
#include "Data/task/taskData.h"

class UserData
{
public:
    UserData(const int id, const QString& n ,const QString& e);
    ~UserData();

    //getters
    QVector<const taskData* > get_tasks()const;
    QString get_email()const;
    QString get_name()const;
    int get_id()const;

    //setters
    void set_task(taskData* t);

private:
    const int m_id;
    QString m_name;
    QString m_email;
    QVector<taskData*> m_tasks;

};

#endif // USERDATA_H
