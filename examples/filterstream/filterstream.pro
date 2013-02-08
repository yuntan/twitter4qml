TEMPLATE = app

INCLUDEPATH += $$PWD/../../src 
DEPENDPATH += $$PWD/../../src

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += quick
} else {
    QT += declarative
}
SOURCES = filterstream.cpp

LIBS += -ltwitter4qml -L$$OUT_PWD/../../src

QMAKE_RPATHDIR += \$\$ORIGIN/../../src
TWITTER4QML_PLUGIN_RPATH = $$join(QMAKE_RPATHDIR, ":")

QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${TWITTER4QML_PLUGIN_RPATH}\'
QMAKE_RPATHDIR =

RESOURCES += \
    filterstream.qrc

OTHER_FILES += \
    main.qml
