INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Users

HEADERS += $$PWD/abstractblockaction.h \
    $$PWD/blocklist.h \
    $$PWD/blockids.h \
    $$PWD/createblock.h \
    $$PWD/destroyblock.h

SOURCES += $$PWD/abstractblockaction.cpp \
    $$PWD/blocklist.cpp \
    $$PWD/blockids.cpp \
    $$PWD/createblock.cpp \
    $$PWD/destroyblock.cpp

# Spam Reporting

HEADERS += $$PWD/reportforspam.h

SOURCES += $$PWD/reportforspam.cpp
