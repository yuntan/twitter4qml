TARGET = QtTwitterAPI
MODULE = twitterapi
QT = core gui network

greaterThan(QT_MAJOR_VERSION, 4) {
    load(qt_module)
} else {
    TEMPLATE = lib
    target.path = $$[QT_INSTALL_LIBS]
    INSTALLS += target
}

include($$PWD/lib.pri)

DEFINES += TWITTER4QML_LIBRARY
