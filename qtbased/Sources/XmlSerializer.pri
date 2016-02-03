INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += $$PWD/xmlserializer.cpp
HEADERS += $$PWD/xmlserializer.h

contains(QT, xml) {
    DEFINES += XML_SUPPORT
}
