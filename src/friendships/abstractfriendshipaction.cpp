#include "abstractfriendshipaction.h"

class AbstractFriendshipAction::Private
{
public:
    Private();

    QString screenName;
    QString userId;
    bool follow;
    bool includeEntities;
};

AbstractFriendshipAction::Private::Private()
    : follow(true)
    , includeEntities(true)
{
}

AbstractFriendshipAction::AbstractFriendshipAction(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

AbstractFriendshipAction::~AbstractFriendshipAction()
{
    delete d;
}

const QString &AbstractFriendshipAction::screenName() const
{
    return d->screenName;
}

void AbstractFriendshipAction::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

const QString &AbstractFriendshipAction::userId() const
{
    return d->userId;
}

void AbstractFriendshipAction::setUserId(const QString &userId)
{
    if (d->userId == userId) return;
    d->userId = userId;
    emit userIdChanged(userId);
}

bool AbstractFriendshipAction::follow() const
{
    return d->follow;
}

void AbstractFriendshipAction::setFollow(bool follow)
{
    if (d->follow == follow) return;
    d->follow = follow;
    emit followChanged(follow);
}

bool AbstractFriendshipAction::includeEntities() const
{
    return d->includeEntities;
}

void AbstractFriendshipAction::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}
