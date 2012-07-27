#include "statuses.h"


#include <QtCore/QDebug>
#include <QtDeclarative/qdeclarative.h>

#define DEBUG() qDebug() << __PRETTY_FUNCTION__ << __LINE__

Statuses::Statuses(QObject *parent)
    : QObject(parent)
{
}
