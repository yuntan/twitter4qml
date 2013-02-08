INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Helper classes

HEADERS += \
    $$PWD/jsonparser.h \
    $$PWD/abstracttwittermodel.h \
    $$PWD/oauthmanager.h \
    $$PWD/hmac_sha1.h \
    $$PWD/abstracttwitteraction.h \
    $$PWD/tweetmanager.h \
    $$PWD/datamanager.h \
    $$PWD/abstracttwittermultipartaction.h

SOURCES += \
    $$PWD/jsonparser.cpp \
    $$PWD/abstracttwittermodel.cpp \
    $$PWD/oauthmanager.cpp \
    $$PWD/hmac_sha1.cpp \
    $$PWD/abstracttwitteraction.cpp \
    $$PWD/tweetmanager.cpp \
    $$PWD/datamanager.cpp \
    $$PWD/abstracttwittermultipartaction.cpp \
