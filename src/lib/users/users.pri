INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Users
PUBLIC_HEADERS += \
    $$PWD/userslookup.h \
    $$PWD/usersshow.h \
    $$PWD/userssearch.h

SOURCES += \
    $$PWD/userslookup.cpp \
    $$PWD/usersshow.cpp \
    $$PWD/userssearch.cpp

# Suggested Users
PUBLIC_HEADERS += \
    $$PWD/userssuggestions.h \
    $$PWD/userssuggestionsslug.h

SOURCES += \
    $$PWD/userssuggestions.cpp \
    $$PWD/userssuggestionsslug.cpp

# Abstract classes
PUBLIC_HEADERS += \
    $$PWD/abstractusersaction.h \
    $$PWD/abstractusersmodel.h
SOURCES += \
    $$PWD/abstractusersaction.cpp \
    $$PWD/abstractusersmodel.cpp

# Spam Reporting
PUBLIC_HEADERS += \
    $$PWD/usersreportspam.h
SOURCES += \
    $$PWD/usersreportspam.cpp
