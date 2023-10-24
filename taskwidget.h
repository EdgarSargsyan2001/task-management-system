#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QPushButton>

class taskWidget : public QWidget
{
public:
    taskWidget(QWidget* parent = nullptr);
    QPushButton *p;
};

#endif // TASKWIDGET_H
