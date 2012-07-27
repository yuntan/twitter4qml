#include "createsavedsearch.h"

class CreateSavedSearch::Private
{
public:
    QString query;
};

CreateSavedSearch::CreateSavedSearch(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

CreateSavedSearch::~CreateSavedSearch()
{
    delete d;
}

const QString &CreateSavedSearch::query() const
{
    return d->query;
}

void CreateSavedSearch::setQuery(const QString &query)
{
    if (d->query == query) return;
    d->query = query;
    emit queryChanged(query);
}

