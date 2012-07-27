#include "totals.h"

class Totals::Private
{
public:
    Private();

    int friends;
    int updates;
    int followers;
    int favorites;
};

Totals::Private::Private()
    : friends(0)
    , updates(0)
    , followers(0)
    , favorites(0)
{
}

Totals::Totals(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

Totals::~Totals()
{
    delete d;
}

int Totals::friends() const
{
    return d->friends;
}

void Totals::setFriends(int friends)
{
    if (d->friends == friends) return;
    d->friends = friends;
    emit friendsChanged(friends);
}

int Totals::updates() const
{
    return d->updates;
}

void Totals::setUpdates(int updates)
{
    if (d->updates == updates) return;
    d->updates = updates;
    emit updatesChanged(updates);
}

int Totals::followers() const
{
    return d->followers;
}

void Totals::setFollowers(int followers)
{
    if (d->followers == followers) return;
    d->followers = followers;
    emit followersChanged(followers);
}

int Totals::favorites() const
{
    return d->favorites;
}

void Totals::setFavorites(int favorites)
{
    if (d->favorites == favorites) return;
    d->favorites = favorites;
    emit favoritesChanged(favorites);
}
