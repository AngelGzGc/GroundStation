#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T10:52:24
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Coms
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialclass.cpp

HEADERS  += mainwindow.h \
    serialclass.h

FORMS    += mainwindow.ui
