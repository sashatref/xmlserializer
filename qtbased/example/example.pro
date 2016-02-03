#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T17:38:17
#
#-------------------------------------------------

QT       += core gui xml widgets

TARGET = untitled1
TEMPLATE = app

include(../Sources/XmlSerializer.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    testobject.h \
    setgetMacro.h

FORMS    += mainwindow.ui
