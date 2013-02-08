QT       += network sql
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += qml
} else {
    QT += declarative
}

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include(./statuses/statuses.pri)
include(./search/search.pri)
include(./directmessages/directmessages.pri)
include(./friendships/friendships.pri)
include(./account/account.pri)
include(./blocks/blocks.pri)
include(./users/users.pri)
include(./favorites/favorites.pri)
include(./lists/lists.pri)
include(./savedsearches/savedsearches.pri)
include(./geo/geo.pri)
include(./trends/trends.pri)
include(./oauth/oauth.pri)
include(./help/help.pri)
include(./application/application.pri)

include(./tools/tools.pri)

SOURCES += $$PWD/twitter4qml.cpp \
    $$PWD/statuses/status.cpp \
    $$PWD/users/user.cpp \
    $$PWD/directmessages/directmessage.cpp \
    $$PWD/lists/list.cpp \
    $$PWD/extra/unionmodel.cpp \
    $$PWD/utils.cpp \
    $$PWD/related_results/showrelatedresults.cpp

HEADERS += $$PWD/twitter4qml.h \
    $$PWD/twitter4qml_global.h \
    $$PWD/statuses/status.h \
    $$PWD/users/user.h \
    $$PWD/directmessages/directmessage.h \
    $$PWD/lists/list.h \
    $$PWD/extra/unionmodel.h \
    $$PWD/utils.h \
    $$PWD/related_results/showrelatedresults.h

OTHER_FILES += \
    $$PWD/tools/datamanager.sql \
    $$PWD/tools/createdb/000.sql \
    $$PWD/tools/createdb/001.sql \
    $$PWD/tools/createdb/002.sql \
    $$PWD/tools/createdb/003.sql \
    $$PWD/tools/createdb/004.sql \
    $$PWD/tools/createdb/005.sql \
    $$PWD/tools/createdb/006.sql

