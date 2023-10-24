#include "userdata.h"

UserData::UserData(const int id,const QString& n,const QString& e)
    :  m_id(id), m_name(n),m_email(e)
{
}

UserData::~UserData(){
    for(int i = 0;i < m_tasks.size(); ++i)
    {
        delete m_tasks[i];
    }
}

QVector<const taskData* > UserData::get_tasks()const{

    QVector<const taskData* > ans;
    for(int i = 0;i < m_tasks.size(); ++i){
        ans.push_back( m_tasks[i]);
    }
    return ans;
}

QString UserData::get_email()const{
    return m_email;
}
QString UserData::get_name()const{
    return m_name;
}
int UserData::get_id()const{
    return m_id;
}
void UserData::set_task(taskData* t){
    m_tasks.push_back(t);
}
