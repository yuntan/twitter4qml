#ifndef TWITTER4QML_GLOBAL_H
#define TWITTER4QML_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtCore/QDebug>

#define DEBUG() qDebug() << __PRETTY_FUNCTION__ << __LINE__

#if defined(TWITTER4QML_LIBRARY)
#  define TWITTER4QML_EXPORT Q_DECL_EXPORT
#else
#  define TWITTER4QML_EXPORT Q_DECL_IMPORT
#endif

#endif // TWITTER4QML_GLOBAL_H
