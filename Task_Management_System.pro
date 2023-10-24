QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Creation/Task/createtask.h \
    Creation/Task/edittask.h \
    Creation/Task/task.h \
    Data/task/taskData.h \
    Data/user/userdata.h \
    Languages/change_language.h \
    RegistrationAndLogin/email_input.h \
    RegistrationAndLogin/email_verification.h \
    RegistrationAndLogin/login.h \
    RegistrationAndLogin/register.h \
    RegistrationAndLogin/reset_password.h \
    SMTP_Socket/smtp.h \
    hellpers/hellpers.h \
    style\line_edit.h \
    style\button.h \
    text\text.h \
    mainwindow.h \

SOURCES += \
    Creation/Task/createtask.cpp \
    Creation/Task/edittask.cpp \
    Creation/Task/task.cpp \
    Data/task/taskData.cpp \
    Data/user/userdata.cpp \
    Languages/change_language.cpp \
    RegistrationAndLogin/email_input.cpp \
    RegistrationAndLogin/email_verification.cpp \
    RegistrationAndLogin/login.cpp \
    RegistrationAndLogin/register.cpp \
    RegistrationAndLogin/reset_password.cpp \
    SMTP_Socket/smtp.cpp \
    main.cpp \
    mainwindow.cpp

FORMS += \
    Creation/Task/task.ui \
    Languages/change_language.ui \
    RegistrationAndLogin/email_input.ui \
    RegistrationAndLogin/email_verification.ui \
    RegistrationAndLogin/login.ui \
    RegistrationAndLogin/register.ui \
    RegistrationAndLogin/reset_password.ui \
    mainwindow.ui \

#LIBS += -L/:/MySql_lib/libmysql.dll -lMyLibrary

TRANSLATIONS += Languages/armenian_language.ts


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
