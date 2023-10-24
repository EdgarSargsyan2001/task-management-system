#ifndef EDITTASK_H
#define EDITTASK_H
#include "task.h"
#include "Data/task/taskData.h"


class editTask : public Task
{
public:
    editTask(const taskData*,QWidget *parent = nullptr);
    void button_clicked();
};

#endif // EDITTASK_H
