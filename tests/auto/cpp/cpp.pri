TEMPLATE = app
QT       += testlib
QT       -= gui
CONFIG   += console testcase
CONFIG   -= app_bundle

INCLUDEPATH += $$PWD/../../../src $$PWD/test
DEPENDPATH += $$PWD/../../../src $$PWD/test
HEADERS += $$PWD/test/abstracttwitter4qmltest.h
SOURCES += $$PWD/test/abstracttwitter4qmltest.cpp

LIBS += -ltwitter4qml -L$$OUT_PWD/../../../../../src

QMAKE_RPATHDIR += \$\$ORIGIN/../../../../../src
TWITTER4QML_PLUGIN_RPATH = $$join(QMAKE_RPATHDIR, ":")

QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${TWITTER4QML_PLUGIN_RPATH}\'
QMAKE_RPATHDIR =
