#ifndef TASKDATA_H
#define TASKDATA_H
#include <QString>
#include <QDate>

class taskData
{
public:
    taskData(int id,const QString& name,const QString& desc,const QDate& date);


    int get_id()const;
    QString get_name()const;
    QString get_description()const;
    QDate get_date()const ;


    void set_name(const QString&);
    void set_description(const QString&);
    void set_date(const QDate&);

private:
    const int m_id;
    QString m_name;
    QString m_description;
    QDate m_date;
};

#endif // TASKDATA_H
