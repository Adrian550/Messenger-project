QT += core network sql
QT -= gui

CONFIG += c++11

TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += core/main.cpp \
    core/server.cpp \
    core/task_manager.cpp \
    client/client.cpp

HEADERS += \
    core/server.h \
    core/task_manager.h \
    client/client.h \
    util/commands.h \
    util/std.h
