INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Favorites
PUBLIC_HEADERS += \
    $$PWD/favoriteslist.h \
    $$PWD/destroyfavorites.h \
    $$PWD/createfavorites.h

SOURCES += \
    $$PWD/favoriteslist.cpp \
    $$PWD/destroyfavorites.cpp \
    $$PWD/createfavorites.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractfavoritesaction.h
SOURCES += \
    $$PWD/abstractfavoritesaction.cpp
