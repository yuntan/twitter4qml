TEMPLATE = subdirs
SUBDIRS = cpp pri

greaterThan(QT_MAJOR_VERSION, 4) {
    SUBDIRS += qml
}
