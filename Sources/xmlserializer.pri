INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += $$PWD/xmlserializer.cpp
HEADERS += $$PWD/xmlserializer.h

LIBS += -L$$PWD/../tinyxml2 -ltinyxml2

INCLUDEPATH += $$PWD/../tinyxml2
DEPENDPATH += $$PWD/../tinyxml2
