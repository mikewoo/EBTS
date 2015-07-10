#-------------------------------------------------
#
# Project created by QtCreator 2014-07-08T15:09:21
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EBTS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    api/myapp.cpp \
    showimage.cpp

HEADERS  += mainwindow.h \
    api/myapp.h \
    showimage.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
