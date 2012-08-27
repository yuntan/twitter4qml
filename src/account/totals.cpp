/* Copyright (c) 2012 Twitter4QML Project.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Twitter4QML nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL TWITTER4QML BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
