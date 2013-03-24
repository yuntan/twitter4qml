INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Friends & Followers
PUBLIC_HEADERS += \
    $$PWD/noretweetids.h \
    $$PWD/friendids.h \
    $$PWD/followerids.h \
    # $$PWD/lookup.h \
    $$PWD/incoming.h \
    $$PWD/outgoing.h \
    $$PWD/createfriendship.h \
    $$PWD/destroyfriendship.h \
    $$PWD/updatefriendship.h \
    $$PWD/showfriendships.h \
    $$PWD/friends.h \
    $$PWD/followers.h

SOURCES += \
    $$PWD/noretweetids.cpp \
    $$PWD/friendids.cpp \
    $$PWD/followerids.cpp \
    # $$PWD/lookup.cpp \
    $$PWD/incoming.cpp \
    $$PWD/outgoing.cpp \
    $$PWD/createfriendship.cpp \
    $$PWD/destroyfriendship.cpp \
    $$PWD/updatefriendship.cpp \
    $$PWD/showfriendships.cpp \
    $$PWD/friends.cpp \
    $$PWD/followers.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractfriendshipidsmodel.h \
    $$PWD/abstractfriendshipaction.h

SOURCES += \
    $$PWD/abstractfriendshipidsmodel.cpp \
    $$PWD/abstractfriendshipaction.cpp
