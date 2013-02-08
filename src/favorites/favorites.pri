INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Favorites
HEADERS += $$PWD/favoriteslist.h \
    $$PWD/destroyfavorite.h \
    $$PWD/createfavorite.h

SOURCES += $$PWD/favoriteslist.cpp \
    $$PWD/destroyfavorite.cpp \
    $$PWD/createfavorite.cpp

# Base classes
HEADERS += $$PWD/abstractfavoriteaction.h
SOURCES += $$PWD/abstractfavoriteaction.cpp
