TARGET = twitter4qml
TEMPLATE = lib

DEFINES += TWITTER4QML_LIBRARY

include($$PWD/src.pri)

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4413797
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = twitter4qml.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

