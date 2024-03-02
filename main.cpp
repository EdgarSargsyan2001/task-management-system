#include <QApplication>
#include <QSqlDatabase>
#include <QSettings>
#include <QFile>

#include "mainwindow.h"
#include "RegistrationAndLogin/login.h"
#include "text/text.h"
#include <QTranslator>
#include "Data/user/userdata.h"
#include <QPushButton>

void set_settings_value();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/img/registr_background.png"));

    if (QFile::copy(":/MySql_lib/libmysql.dll", "libmysql.dll" )) {
        qDebug() << "DLL extracted successfully.";
    } else {
        qDebug() << "Failed to extract the DLL.";
    }

    set_settings_value();

    QTranslator translator;
    translator.setObjectName(Text::english);

    login l(&translator);


    QObject::connect(&l,login::loginSuccess,[&l,&translator](UserData* data){
        MainWindow *w = new MainWindow(&translator,*data);
//        qDebug()<<(int*)w;

        QObject::connect(w,MainWindow::changeLanguage,&l,login::update_ui);
        QObject::connect(w,MainWindow::log_out,&l,login::show);
        QObject::connect(w,MainWindow::log_out,[w](){delete w; });

        w->show();
    });

    l.show();

    return a.exec();
}

void set_settings_value(){
    QSettings settings(".env", QSettings::IniFormat);
    //database
    settings.setValue("DATABASE_NAME", "");
    settings.setValue("HOST", "");
    settings.setValue("PASSWORD", "");
    settings.setValue("USER_NAME", "");

    //SMTP
    settings.setValue("SMTP_HOST", "");
    settings.setValue("SMTP_PASSWORD", "");
    settings.setValue("SMTP_PORT", "");
    settings.setValue("SMTP_SENDER", "");
    settings.setValue("SMTP_USERNAME", "");

}
