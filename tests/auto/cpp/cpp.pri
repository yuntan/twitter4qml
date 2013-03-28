TEMPLATE = app
CONFIG   += console testcase
QT       += testlib
QT       -= gui
CONFIG   -= app_bundle

INCLUDEPATH += $$PWD/test/
DEPENDPATH += $$PWD/test/
HEADERS += $$PWD/test/abstracttwitter4qmltest.h
SOURCES += $$PWD/test/abstracttwitter4qmltest.cpp

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += twitterapi-private
} else {
    INCLUDEPATH += \
        $$PWD/../../../src/lib/oauth/ \
        $$PWD/../../../src/lib/tools/ \
        $$PWD/../../../src/lib/statuses/ \
        $$PWD/../../../src/lib/account/ \
        $$PWD/../../../src/lib/trends/ \
        $$PWD/../../../src/lib/users/ \
        $$PWD/../../../src/lib/help/ \
        $$PWD/../../../src/lib/search/ \
        $$PWD/../../../src/lib/friendships/ \
        $$PWD/../../../src/lib/

    DEPENDPATH += \
        $$PWD/../../../src/lib/oauth/ \
        $$PWD/../../../src/lib/tools/ \
        $$PWD/../../../src/lib/statuses/ \
        $$PWD/../../../src/lib/account/ \
        $$PWD/../../../src/lib/trends/ \
        $$PWD/../../../src/lib/users/ \
        $$PWD/../../../src/lib/help/ \
        $$PWD/../../../src/lib/search/ \
        $$PWD/../../../src/lib/friendships/ \
        $$PWD/../../../src/lib/

    LIBS += -lQtTwitterAPI -L$$OUT_PWD/../../../../../src/lib/

    QMAKE_RPATHDIR += \$\$ORIGIN/../../../../../src/lib
    TWITTER4QML_PLUGIN_RPATH = $$join(QMAKE_RPATHDIR, ":")

    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${TWITTER4QML_PLUGIN_RPATH}\'
    QMAKE_RPATHDIR =
}
