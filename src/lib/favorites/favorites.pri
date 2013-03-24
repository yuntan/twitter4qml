INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Favorites
PUBLIC_HEADERS += \
    $$PWD/favoriteslist.h \
    $$PWD/destroyfavorite.h \
    $$PWD/createfavorite.h

SOURCES += \
    $$PWD/favoriteslist.cpp \
    $$PWD/destroyfavorite.cpp \
    $$PWD/createfavorite.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractfavoriteaction.h
SOURCES += \
    $$PWD/abstractfavoriteaction.cpp
