INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Block

PUBLIC_HEADERS += \
    $$PWD/abstractblockaction.h \
    $$PWD/blocklist.h \
    $$PWD/blockids.h \
    $$PWD/createblock.h \
    $$PWD/destroyblock.h

SOURCES += \
    $$PWD/abstractblockaction.cpp \
    $$PWD/blocklist.cpp \
    $$PWD/blockids.cpp \
    $$PWD/createblock.cpp \
    $$PWD/destroyblock.cpp

# Spam Reporting

PUBLIC_HEADERS += \
    $$PWD/reportforspam.h

SOURCES += \
    $$PWD/reportforspam.cpp
