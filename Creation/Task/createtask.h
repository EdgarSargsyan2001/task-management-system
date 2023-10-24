#ifndef CREATETASK_H
#define CREATETASK_H
#include "task.h"
#include "Data/user/userdata.h"

class createTask: public Task
{
public:
    createTask(const UserData* const uD,QWidget *parent = nullptr);
//    ~createTask();

public slots:
    void create_button_clicked();

private:
    const UserData *const m_userData;
};

#endif // CREATETASK_H
