#include "abstractuseraction.h"

class AbstractUserAction::Private
{
public:
    Private();

    QString userId;
    QString screenName;
    bool includeEntities;
};

AbstractUserAction::Private::Private()
    : includeEntities(true)
{
}

AbstractUserAction::AbstractUserAction(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

AbstractUserAction::~AbstractUserAction()
{
    delete d;
}

const QString &AbstractUserAction::userId() const
{
    return d->userId;
}

void AbstractUserAction::setUserId(const QString &userId)
{
    if (d->userId == userId) return;
    d->userId = userId;
    emit userIdChanged(userId);
}

const QString &AbstractUserAction::screenName() const
{
    return d->screenName;
}

void AbstractUserAction::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

bool AbstractUserAction::includeEntities() const
{
    return d->includeEntities;
}

void AbstractUserAction::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}
