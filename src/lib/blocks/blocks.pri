INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Blocks

PUBLIC_HEADERS += \
    $$PWD/abstractblocksaction.h \
    $$PWD/blockslist.h \
    $$PWD/blocksids.h \
    $$PWD/createblocks.h \
    $$PWD/destroyblocks.h

SOURCES += \
    $$PWD/abstractblocksaction.cpp \
    $$PWD/blockslist.cpp \
    $$PWD/blocksids.cpp \
    $$PWD/createblocks.cpp \
    $$PWD/destroyblocks.cpp

# Spam Reporting

PUBLIC_HEADERS += \
    $$PWD/reportforspam.h

SOURCES += \
    $$PWD/reportforspam.cpp
