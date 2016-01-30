QT += core
QT -= gui

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

isEmpty(MYCOMPILER_POSTFIX) {
    MYCOMPILER_POSTFIX = _vc12
}

include(../Sources/xmlserializer.pri)

CONFIG(debug, debug|release) {
    TARGET = XmlSerializerTest$${MYCOMPILER_POSTFIX}_d
}
CONFIG(release, debug|release) {
    TARGET = XmlSerializerTest$${MYCOMPILER_POSTFIX}
}

isEmpty(DESTDIR) {
    DESTDIR = ../Builds
    DESTDIR_TARGET = ../Builds
}

SOURCES += main.cpp \
    myclass.cpp

HEADERS += \
    myclass.h \



