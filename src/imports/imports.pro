TARGETPATH = TwitterAPI
greaterThan(QT_MAJOR_VERSION, 4) {
    TARGET = twitterapi
    IMPORT_VERSION = 1.1
    load(qml_plugin)

    QT += qml twitterapi
    LIBS += -L$$QT.twitterapi.libs
    OTHER_FILES = plugins.qmltypes
} else {
    TEMPLATE = lib
    TARGET = declarative_twitterapi
    CONFIG += qt plugin
    QT += declarative

    INCLUDEPATH += \
        $$PWD/../lib/statuses/ \
        $$PWD/../lib/tools/ \
        $$PWD/../lib/directmessages/ \
        $$PWD/../lib/friendships/ \
        $$PWD/../lib/users/ \
        $$PWD/../lib/account/ \
        $$PWD/../lib/blocks/ \
        $$PWD/../lib/favorites/ \
        $$PWD/../lib/lists/ \
        $$PWD/../lib/savedsearches/ \
        $$PWD/../lib/geo/ \
        $$PWD/../lib/trends/ \
        $$PWD/../lib/oauth/ \
        $$PWD/../lib/help/ \
        $$PWD/../lib/application/ \
        $$PWD/../lib/related_results/ \
        $$PWD/../lib/search/ \
        $$PWD/../lib/

    DEPENDPATH += \
        $$PWD/../lib/statuses/ \
        $$PWD/../lib/tools/ \
        $$PWD/../lib/directmessages/ \
        $$PWD/../lib/friendships/ \
        $$PWD/../lib/users/ \
        $$PWD/../lib/account/ \
        $$PWD/../lib/blocks/ \
        $$PWD/../lib/favorites/ \
        $$PWD/../lib/lists/ \
        $$PWD/../lib/savedsearches/ \
        $$PWD/../lib/geo/ \
        $$PWD/../lib/trends/ \
        $$PWD/../lib/oauth/ \
        $$PWD/../lib/help/ \
        $$PWD/../lib/application/ \
        $$PWD/../lib/related_results/ \
        $$PWD/../lib/search/ \
        $$PWD/../lib/

    LIBS += -lQtTwitterAPI -L$$OUT_PWD/../lib/

    QMAKE_RPATHDIR += \$\$ORIGIN/../lib
    TWITTER4QML_PLUGIN_RPATH = $$join(QMAKE_RPATHDIR, ":")

    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$${TWITTER4QML_PLUGIN_RPATH}\'
    QMAKE_RPATHDIR =

    DESTDIR = $${OUT_PWD}/TwitterAPI
    target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

    qmldir.files += $$PWD/qmldir
    qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH
    INSTALLS += target qmldir

    QMLDIRFILE = $${PWD}/qmldir
    copy2build.input = QMLDIRFILE
    copy2build.output = $${OUT_PWD}/TwitterAPI/qmldir
    !contains(TEMPLATE_PREFIX, vc): copy2build.variable_out = PRE_TARGETDEPS
    copy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
    copy2build.name = COPY ${QMAKE_FILE_IN}
    copy2build.CONFIG += no_link
    # `clean' should leave the build in a runnable state, which means it shouldn't delete qmldir
    copy2build.CONFIG += no_clean
    QMAKE_EXTRA_COMPILERS += copy2build
}

SOURCES += main.cpp


