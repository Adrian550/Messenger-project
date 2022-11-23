#-------------------------------------------------
#
# Project created by QtCreator 2016-04-23T20:02:32
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Client
TEMPLATE = app


SOURCES += core/main.cpp\
    core/user.cpp \
    connection/connection.cpp \
    task-manager/task_manager.cpp \
    core/contact.cpp

HEADERS  += \
    core/user.h \
    connection/connection.h \
    task-manager/task_manager.h \
    core/contact.h \
    util/commands.h \
    util/std.h

FORMS    +=

RESOURCES += \
    res.qrc
