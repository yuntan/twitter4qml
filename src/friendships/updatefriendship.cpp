#include "updatefriendship.h"

class UpdateFriendship::Private
{
public:
    Private();

    QString userId;
    QString screenName;
    bool device;
    bool retweets;
};

UpdateFriendship::Private::Private()
    : device(false)
    , retweets(true)
{

}

UpdateFriendship::UpdateFriendship(QVariantMap parameters, QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
    setParameters(parameters);
}

UpdateFriendship::~UpdateFriendship()
{
    delete d;
}

const QString &UpdateFriendship::userId() const
{
    return d->userId;
}

void UpdateFriendship::setUserId(const QString &userId)
{
    if (d->userId == userId) return;
    d->userId = userId;
    emit userIdChanged(userId);
}

const QString &UpdateFriendship::screenName() const
{
    return d->screenName;
}

void UpdateFriendship::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

bool UpdateFriendship::device() const
{
    return d->device;
}

void UpdateFriendship::setDevice(bool device)
{
    if (d->device == device) return;
    d->device = device;
    emit deviceChanged(device);
}

bool UpdateFriendship::retweets() const
{
    return d->retweets;
}

void UpdateFriendship::setRetweets(bool retweets)
{
    if (d->retweets == retweets) return;
    d->retweets = retweets;
    emit retweetsChanged(retweets);
}
