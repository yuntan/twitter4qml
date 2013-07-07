INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Lists
PUBLIC_HEADERS += \
    $$PWD/abstractlistsaction.h \
    $$PWD/lists.h \
    $$PWD/listsstatuses.h \
    $$PWD/listsmemberships.h \
    $$PWD/createlistssubscribers.h \
    $$PWD/destroylistssubscribers.h \
    $$PWD/listsmembers.h \
    $$PWD/destroylists.h \
    $$PWD/updatelists.h \
    $$PWD/createlists.h \
    $$PWD/showlists.h \
    $$PWD/listssubscriptions.h

SOURCES += \
    $$PWD/abstractlistsaction.cpp \
    $$PWD/lists.cpp \
    $$PWD/listsstatuses.cpp \
    $$PWD/listsmemberships.cpp \
    $$PWD/createlistssubscribers.cpp \
    $$PWD/destroylistssubscribers.cpp \
    $$PWD/listsmembers.cpp \
    $$PWD/destroylists.cpp \
    $$PWD/updatelists.cpp \
    $$PWD/createlists.cpp \
    $$PWD/showlists.cpp \
    $$PWD/listssubscriptions.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractlistsmodel.h
SOURCES += \
    $$PWD/abstractlistsmodel.cpp
