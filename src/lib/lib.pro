TARGET = QtTwitterAPI
MODULE = twitterapi
QT = core gui network

greaterThan(QT_MAJOR_VERSION, 4) {
    load(qt_module)
} else {
    TEMPLATE = lib
}

include($$PWD/lib.pri)

DEFINES += TWITTER4QML_LIBRARY
