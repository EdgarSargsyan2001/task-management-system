#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTranslator>
#include "Data/task/taskData.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class UserData;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QTranslator*, UserData& ud, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void log_out();
    void changeLanguage();

public slots:
    void update_ui();
    void show_data();

private slots:
    void on_actionlog_out_triggered();
    void on_actionSecurity_triggered();
    void on_actionlanguage_triggered();
    void on_pushButton_clicked();

private:
    void add_task_ui(const taskData*);
private:
    Ui::MainWindow *ui;
    UserData& m_user_data;
    QTranslator* m_translator = nullptr;

};
#endif // MAINWINDOW_H
