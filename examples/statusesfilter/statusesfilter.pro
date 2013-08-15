TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += quick twitterapi
} else {
    QT += declarative
    INCLUDEPATH += $$PWD/../../src/lib/ $$PWD/../../src/lib/oauth/ $$PWD/../../src/lib/tools/
    DEPENDPATH += $$PWD/../../src/lib/ $$PWD/../../src/lib/oauth/ $$PWD/../../src/lib/tools/
    LIBS += -lQtTwitterAPI -L$$OUT_PWD/../../src/lib/

    QMAKE_RPATHDIR += \$\$ORIGIN/../../src/lib/
    TWITTER4QML_PLUGIN_RPATH = $$join(QMAKE_RPATHDIR, ":")

    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${TWITTER4QML_PLUGIN_RPATH}\'
    QMAKE_RPATHDIR =
}

SOURCES = statusesfilter.cpp

RESOURCES += \
    statusesfilter.qrc

OTHER_FILES += \
    main.qml
