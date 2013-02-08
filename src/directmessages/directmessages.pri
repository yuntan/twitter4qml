INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Direct Messages
HEADERS += $$PWD/directmessages.h \
    $$PWD/directmessagessent.h \
    $$PWD/showdirectmessage.h \
    $$PWD/destroydirectmessage.h \
    $$PWD/newdirectmessage.h

SOURCES += $$PWD/directmessages.cpp \
    $$PWD/directmessagessent.cpp \
    $$PWD/showdirectmessage.cpp \
    $$PWD/destroydirectmessage.cpp \
    $$PWD/newdirectmessage.cpp

# Base classes
HEADERS += $$PWD/abstractdirectmessagesmodel.h \
    $$PWD/abstractdirectmessageaction.h

SOURCES += $$PWD/abstractdirectmessagesmodel.cpp \
    $$PWD/abstractdirectmessageaction.cpp
