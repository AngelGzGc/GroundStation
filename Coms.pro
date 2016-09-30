#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T10:52:24
#
#-------------------------------------------------

QT       += core gui
QT       += serialport quick qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Coms
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialclass.cpp \
    logger.cpp

HEADERS  += mainwindow.h \
    serialclass.h \
    logger.h

FORMS    += mainwindow.ui

DISTFILES += \
    main.qml \
    Logo_LEEM__1__400x400.jpg
