INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Timelines
PUBLIC_HEADERS += \
    $$PWD/statusesmentionstimeline.h \
    $$PWD/statusesusertimeline.h \
    $$PWD/statuseshometimeline.h \
    $$PWD/statusesretweetsofme.h

SOURCES += \
    $$PWD/statusesmentionstimeline.cpp \
    $$PWD/statusesusertimeline.cpp \
    $$PWD/statuseshometimeline.cpp \
    $$PWD/statusesretweetsofme.cpp

# Tweets
PUBLIC_HEADERS += \
    $$PWD/statusesretweets.h \
    $$PWD/statusesshow.h \
    $$PWD/statusesdestroy.h \
    $$PWD/statusesupdate.h \
    $$PWD/statusesretweet.h \
    $$PWD/statusesupdatewithmedia.h

SOURCES += \
    $$PWD/statusesretweets.cpp \
    $$PWD/statusesshow.cpp \
    $$PWD/statusesdestroy.cpp \
    $$PWD/statusesupdate.cpp \
    $$PWD/statusesretweet.cpp \
    $$PWD/statusesupdatewithmedia.cpp

# Streaming
PUBLIC_HEADERS += \
    $$PWD/statusesfilter.h \
    $$PWD/userstream.h \
    $$PWD/statusessample.h

SOURCES += \
    $$PWD/statusesfilter.cpp \
    $$PWD/userstream.cpp \
    $$PWD/statusessample.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractstatusesmodel.h \
    $$PWD/abstractidsmodel.h \
    $$PWD/abstractstatusaction.h

SOURCES += \
    $$PWD/abstractstatusesmodel.cpp \
    $$PWD/abstractidsmodel.cpp \
    $$PWD/abstractstatusaction.cpp
