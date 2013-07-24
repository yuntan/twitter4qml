INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Friends & Followers
PUBLIC_HEADERS += \
    $$PWD/friendshipsnoretweetsids.h \
    $$PWD/friendsids.h \
    $$PWD/followersids.h \
    # $$PWD/lookup.h \
    $$PWD/friendshipsincoming.h \
    $$PWD/friendshipsoutgoing.h \
    $$PWD/friendshipscreate.h \
    $$PWD/friendshipsdestroy.h \
    $$PWD/friendshipsupdate.h \
    $$PWD/friendshipsshow.h \
    $$PWD/friendslist.h \
    $$PWD/followerslist.h

SOURCES += \
    $$PWD/friendshipsnoretweetsids.cpp \
    $$PWD/friendsids.cpp \
    $$PWD/followersids.cpp \
    # $$PWD/lookup.cpp \
    $$PWD/friendshipsincoming.cpp \
    $$PWD/friendshipsoutgoing.cpp \
    $$PWD/friendshipscreate.cpp \
    $$PWD/friendshipsdestroy.cpp \
    $$PWD/friendshipsupdate.cpp \
    $$PWD/friendshipsshow.cpp \
    $$PWD/friendslist.cpp \
    $$PWD/followerslist.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractfriendshipsidsmodel.h \
    $$PWD/abstractfriendshipsaction.h

SOURCES += \
    $$PWD/abstractfriendshipsidsmodel.cpp \
    $$PWD/abstractfriendshipsaction.cpp
