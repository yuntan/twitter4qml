INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Direct Messages
PUBLIC_HEADERS += \
    $$PWD/directmessages.h \
    $$PWD/directmessagessent.h \
    $$PWD/showdirectmessages.h \
    $$PWD/destroydirectmessages.h \
    $$PWD/newdirectmessages.h

SOURCES += \
    $$PWD/directmessages.cpp \
    $$PWD/directmessagessent.cpp \
    $$PWD/showdirectmessages.cpp \
    $$PWD/destroydirectmessages.cpp \
    $$PWD/newdirectmessages.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractdirectmessagesmodel.h \
    $$PWD/abstractdirectmessagesaction.h

SOURCES += \
    $$PWD/abstractdirectmessagesmodel.cpp \
    $$PWD/abstractdirectmessagesaction.cpp
