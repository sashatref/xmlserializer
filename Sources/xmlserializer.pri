INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += $$PWD/xmlserializer.cpp
HEADERS += $$PWD/xmlserializer.h

LIBS += -L$$PWD/../tinyxml2/Builds

CONFIG(debug, debug|release) {
    LIBS += -ltinyxml2_d
}
CONFIG(release, debug|release) {
    LIBS += -ltinyxml2
}

INCLUDEPATH += $$PWD/../tinyxml2/Sources
DEPENDPATH += $$PWD/../tinyxml2/Sources
