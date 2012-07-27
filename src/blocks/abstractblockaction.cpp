#include "abstractblockaction.h"

class AbstractBlockAction::Private
{
public:
    Private();

    QString screenName;
    QString userId;
    bool includeEntities;
    bool skipStatus;
};

AbstractBlockAction::Private::Private()
    : includeEntities(true)
    , skipStatus(false)
{
}

AbstractBlockAction::AbstractBlockAction(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

AbstractBlockAction::~AbstractBlockAction()
{
    delete d;
}

const QString &AbstractBlockAction::screenName() const
{
    return d->screenName;
}

void AbstractBlockAction::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

const QString &AbstractBlockAction::userId() const
{
    return d->userId;
}

void AbstractBlockAction::setUserId(const QString &userId)
{
    if (d->userId == userId) return;
    d->userId = userId;
    emit userIdChanged(userId);
}

bool AbstractBlockAction::includeEntities() const
{
    return d->includeEntities;
}

void AbstractBlockAction::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}

bool AbstractBlockAction::skipStatus() const
{
    return d->skipStatus;
}

void AbstractBlockAction::setSkipStatus(bool skipStatus)
{
    if (d->skipStatus == skipStatus) return;
    d->skipStatus = skipStatus;
    emit skipStatusChanged(skipStatus);
}
