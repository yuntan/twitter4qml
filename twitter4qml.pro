greaterThan(QT_MAJOR_VERSION, 4) {
    load(qt_parts)
    OTHER_FILES += .qmake.conf sync.profile
} else {
    TEMPLATE = subdirs
    CONFIG += ordered
    SUBDIRS = src examples tests
}
OTHER_FILES += LICENSE
