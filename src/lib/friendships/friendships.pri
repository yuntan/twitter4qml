INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Friends & Followers
PUBLIC_HEADERS += \
    $$PWD/noretweetsids.h \
    $$PWD/friendsids.h \
    $$PWD/followersids.h \
    # $$PWD/lookup.h \
    $$PWD/incoming.h \
    $$PWD/outgoing.h \
    $$PWD/createfriendships.h \
    $$PWD/destroyfriendships.h \
    $$PWD/updatefriendships.h \
    $$PWD/showfriendships.h \
    $$PWD/friends.h \
    $$PWD/followers.h

SOURCES += \
    $$PWD/noretweetsids.cpp \
    $$PWD/friendsids.cpp \
    $$PWD/followersids.cpp \
    # $$PWD/lookup.cpp \
    $$PWD/incoming.cpp \
    $$PWD/outgoing.cpp \
    $$PWD/createfriendships.cpp \
    $$PWD/destroyfriendships.cpp \
    $$PWD/updatefriendships.cpp \
    $$PWD/showfriendships.cpp \
    $$PWD/friends.cpp \
    $$PWD/followers.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractfriendshipsidsmodel.h \
    $$PWD/abstractfriendshipsaction.h

SOURCES += \
    $$PWD/abstractfriendshipsidsmodel.cpp \
    $$PWD/abstractfriendshipsaction.cpp
