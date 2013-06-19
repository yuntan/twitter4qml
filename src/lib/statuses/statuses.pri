INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Timelines
PUBLIC_HEADERS += \
    $$PWD/mentionstimeline.h \
    $$PWD/usertimeline.h \
    $$PWD/hometimeline.h \
    $$PWD/retweetsofme.h

SOURCES += \
    $$PWD/mentionstimeline.cpp \
    $$PWD/usertimeline.cpp \
    $$PWD/hometimeline.cpp \
    $$PWD/retweetsofme.cpp

# Tweets
PUBLIC_HEADERS += \
    $$PWD/retweets.h \
    $$PWD/showstatus.h \
    $$PWD/destroystatus.h \
    $$PWD/updatestatus.h \
    $$PWD/retweetstatus.h \
    $$PWD/updatestatuswithmedia.h

SOURCES += \
    $$PWD/retweets.cpp \
    $$PWD/showstatus.cpp \
    $$PWD/destroystatus.cpp \
    $$PWD/updatestatus.cpp \
    $$PWD/retweetstatus.cpp \
    $$PWD/updatestatuswithmedia.cpp

# Streaming
PUBLIC_HEADERS += \
    $$PWD/filterstream.h \
    $$PWD/userstream.h \
    $$PWD/samplestream.h

SOURCES += \
    $$PWD/filterstream.cpp \
    $$PWD/userstream.cpp \
    $$PWD/samplestream.cpp

# Secret APIs
PUBLIC_HEADERS += \
    $$PWD/activitysummary.h
SOURCES += \
    $$PWD/activitysummary.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractstatusesmodel.h \
    $$PWD/abstractidsmodel.h \
    $$PWD/abstractstatusaction.h

SOURCES += \
    $$PWD/abstractstatusesmodel.cpp \
    $$PWD/abstractidsmodel.cpp \
    $$PWD/abstractstatusaction.cpp
