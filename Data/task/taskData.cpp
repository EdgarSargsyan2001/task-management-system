#include "taskdata.h"

taskData::taskData(int id,const QString& name,const QString& desc,const QDate& date)
    :m_id(id), m_name(name), m_description(desc) , m_date(date)
{

}

int taskData::get_id()const{
    return m_id;
}
QString taskData::get_name()const{
    return m_name;
}
QString taskData::get_description()const{
    return m_description;
}
QDate taskData::get_date()const {
    return m_date;
}


void taskData::set_name(const QString& n){
    m_name = n;
}

void taskData::set_description(const QString& d){
    m_description = d;
}

void taskData::set_date(const QDate& d){
    m_date = d;
}
