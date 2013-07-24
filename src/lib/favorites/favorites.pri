INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Favorites
PUBLIC_HEADERS += \
    $$PWD/favoriteslist.h \
    $$PWD/favoritesdestroy.h \
    $$PWD/favoritescreate.h

SOURCES += \
    $$PWD/favoriteslist.cpp \
    $$PWD/favoritesdestroy.cpp \
    $$PWD/favoritescreate.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractfavoritesaction.h
SOURCES += \
    $$PWD/abstractfavoritesaction.cpp
