#include "noretweetids.h"

class NoRetweetIds::Private
{
public:
    Private();
    bool stringifyIds;
};

NoRetweetIds::Private::Private()
    : stringifyIds(true)
{}

NoRetweetIds::NoRetweetIds(QObject *parent)
    : AbstractIdsModel(parent)
    , d(new Private)
{
}

NoRetweetIds::~NoRetweetIds()
{
    delete d;
}

void NoRetweetIds::parseDone(const QVariant &result)
{
    DEBUG() << result;
    AbstractIdsModel::parseDone(result);
}

bool NoRetweetIds::stringifyIds() const
{
    return d->stringifyIds;
}

void NoRetweetIds::setStringifyIds(bool stringifyIds)
{
    if (d->stringifyIds == stringifyIds) return;
    d->stringifyIds = stringifyIds;
    emit stringifyIdsChanged(stringifyIds);
}
