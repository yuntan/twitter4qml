INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Helper classes

PUBLIC_HEADERS += \
    $$PWD/abstracttwittermodel.h \
    $$PWD/oauthmanager.h \
    $$PWD/abstracttwitteraction.h

PUBLIC_HEADERS += \
    $$PWD/jsonparser.h \
    $$PWD/hmac_sha1.h \
    $$PWD/tweetmanager.h \
    $$PWD/datamanager.h \
    $$PWD/abstracttwittermultipartaction.h

SOURCES += \
    $$PWD/jsonparser.cpp \
    $$PWD/hmac_sha1.cpp \
    $$PWD/tweetmanager.cpp \
    $$PWD/datamanager.cpp \
    $$PWD/abstracttwittermultipartaction.cpp \
    $$PWD/abstracttwittermodel.cpp \
    $$PWD/oauthmanager.cpp \
    $$PWD/abstracttwitteraction.cpp
