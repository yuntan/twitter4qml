#include "destroysavedsearch.h"

class DestroySavedSearch::Private
{
public:
    QString id;
};

DestroySavedSearch::DestroySavedSearch(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

DestroySavedSearch::~DestroySavedSearch()
{
    delete d;
}

const QString &DestroySavedSearch::id() const
{
    return d->id;
}

void DestroySavedSearch::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

