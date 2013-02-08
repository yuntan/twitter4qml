INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Users
HEADERS += $$PWD/lookupusers.h \
    $$PWD/showuser.h \
    $$PWD/searchusers.h

SOURCES += $$PWD/lookupusers.cpp \
    $$PWD/showuser.cpp \
    $$PWD/searchusers.cpp

# Suggested Users
HEADERS += $$PWD/slugs.h \
    $$PWD/suggestions.h

SOURCES += $$PWD/slugs.cpp \
    $$PWD/suggestions.cpp

# Base classes
HEADERS += $$PWD/abstractuseraction.h \
    $$PWD/abstractusersmodel.h
SOURCES += $$PWD/abstractuseraction.cpp \
    $$PWD/abstractusersmodel.cpp
