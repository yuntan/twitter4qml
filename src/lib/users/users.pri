INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Users
PUBLIC_HEADERS += \
    $$PWD/lookupusers.h \
    $$PWD/showuser.h \
    $$PWD/searchusers.h

SOURCES += \
    $$PWD/lookupusers.cpp \
    $$PWD/showuser.cpp \
    $$PWD/searchusers.cpp

# Suggested Users
PUBLIC_HEADERS += \
    $$PWD/slugs.h \
    $$PWD/suggestions.h

SOURCES += \
    $$PWD/slugs.cpp \
    $$PWD/suggestions.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractuseraction.h \
    $$PWD/abstractusersmodel.h
SOURCES += \
    $$PWD/abstractuseraction.cpp \
    $$PWD/abstractusersmodel.cpp
