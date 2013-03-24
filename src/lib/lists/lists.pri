INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Lists
PUBLIC_HEADERS += \
    $$PWD/abstractlistaction.h \
    $$PWD/lists.h \
    $$PWD/liststatuses.h \
    $$PWD/listsmemberships.h \
    $$PWD/subscribelist.h \
    $$PWD/unsubscribelist.h \
    $$PWD/listmembers.h \
    $$PWD/destroylist.h \
    $$PWD/updatelist.h \
    $$PWD/createlist.h \
    $$PWD/showlist.h \
    $$PWD/listssubscriptions.h

SOURCES += \
    $$PWD/abstractlistaction.cpp \
    $$PWD/lists.cpp \
    $$PWD/liststatuses.cpp \
    $$PWD/listsmemberships.cpp \
    $$PWD/subscribelist.cpp \
    $$PWD/unsubscribelist.cpp \
    $$PWD/listmembers.cpp \
    $$PWD/destroylist.cpp \
    $$PWD/updatelist.cpp \
    $$PWD/createlist.cpp \
    $$PWD/showlist.cpp \
    $$PWD/listssubscriptions.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractlistsmodel.h
SOURCES += \
    $$PWD/abstractlistsmodel.cpp
