INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Direct Messages
PUBLIC_HEADERS += \
    $$PWD/directmessages.h \
    $$PWD/directmessagessent.h \
    $$PWD/directmessagesshow.h \
    $$PWD/directmessagesdestroy.h \
    $$PWD/directmessagesnew.h

SOURCES += \
    $$PWD/directmessages.cpp \
    $$PWD/directmessagessent.cpp \
    $$PWD/directmessagesshow.cpp \
    $$PWD/directmessagesdestroy.cpp \
    $$PWD/directmessagesnew.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractdirectmessagesmodel.h \
    $$PWD/abstractdirectmessagesaction.h

SOURCES += \
    $$PWD/abstractdirectmessagesmodel.cpp \
    $$PWD/abstractdirectmessagesaction.cpp
