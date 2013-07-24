INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Lists
PUBLIC_HEADERS += \
    $$PWD/abstractlistsaction.h \
    $$PWD/listslist.h \
    $$PWD/listsstatuses.h \
    $$PWD/listsmemberships.h \
    $$PWD/listssubscriberscreate.h \
    $$PWD/listssubscribersdestroy.h \
    $$PWD/listsmembers.h \
    $$PWD/listsdestroy.h \
    $$PWD/listsupdate.h \
    $$PWD/listscreate.h \
    $$PWD/listsshow.h \
    $$PWD/listssubscriptions.h

SOURCES += \
    $$PWD/abstractlistsaction.cpp \
    $$PWD/listslist.cpp \
    $$PWD/listsstatuses.cpp \
    $$PWD/listsmemberships.cpp \
    $$PWD/listssubscriberscreate.cpp \
    $$PWD/listssubscribersdestroy.cpp \
    $$PWD/listsmembers.cpp \
    $$PWD/listsdestroy.cpp \
    $$PWD/listsupdate.cpp \
    $$PWD/listscreate.cpp \
    $$PWD/listsshow.cpp \
    $$PWD/listssubscriptions.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractlistsmodel.h
SOURCES += \
    $$PWD/abstractlistsmodel.cpp
