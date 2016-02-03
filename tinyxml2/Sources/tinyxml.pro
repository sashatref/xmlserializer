
DEFINES += TINYXML2_EXPORT

isEmpty(DESTDIR) {
    DESTDIR = ../Builds
    DESTDIR_TARGET = ../Builds
}

TEMPLATE = lib

#CONFIG += staticlib

CONFIG(debug, debug|release) {
    TARGET = TinyXml2_d
}
CONFIG(release, debug|release) {
    TARGET = TinyXml2
}

HEADERS += \
    tinyxml2.h


SOURCES += \
    tinyxml2.cpp

