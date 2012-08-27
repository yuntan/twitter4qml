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

#include "favorite.h"

#include "createfavorite.h"
#include "destroyfavorite.h"

#include "../statuses/showstatus.h"

class Favorite::Private : public QObject
{
    Q_OBJECT
public:
    Private(Favorite *parent);

    bool loading;
    QString id;
    bool favorited;

private slots:
    void setLoading(bool loading);
    void idChanged(const QString &id);
    void favoritedChanged(bool favorited);
    void dataChanged(const QVariantMap &data);

private:
    Favorite *q;
    QList<AbstractTwitterAction *> tasks;
};

Favorite::Private::Private(Favorite *parent)
    : QObject(parent)
    , loading(false)
    , favorited(false)
    , q(parent)
{
    connect(q, SIGNAL(idChanged(QString)), this, SLOT(idChanged(QString)));
//    connect(q, SIGNAL(favoritedChanged(bool)), this, SLOT(favoritedChanged(bool)));
}

void Favorite::Private::setLoading(bool l)
{
    if (loading == l) return;
    loading = l;
    emit q->loadingChanged(l);
}

void Favorite::Private::idChanged(const QString &id)
{
    ShowStatus *action = new ShowStatus(this);
    action->setId(id);
    action->setTrimUser(true);
    action->setIncludeEntities(false);
    connect(action, SIGNAL(dataChanged(QVariantMap)), this, SLOT(dataChanged(QVariantMap)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void Favorite::Private::favoritedChanged(bool favorited)
{
    AbstractFavoriteAction *action = 0;
    if (favorited) {
        action = new CreateFavorite(this);
    } else {
        action = new DestroyFavorite(this);
    }
    action->setId(id);
    action->setIncludeEntities(false);
    connect(action, SIGNAL(dataChanged(QVariantMap)), this, SLOT(dataChanged(QVariantMap)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void Favorite::Private::dataChanged(const QVariantMap &data)
{
    AbstractTwitterAction *action = qobject_cast<AbstractTwitterAction *>(sender());
    if (action) {
        disconnect(q, SIGNAL(favoritedChanged(bool)), this, SLOT(favoritedChanged(bool)));
        if (qobject_cast<AbstractFavoriteAction *>(sender())) {
            q->setFavorited(!data.value("favorited").toBool());
        } else {
            q->setFavorited(data.value("favorited").toBool());
        }
        connect(q, SIGNAL(favoritedChanged(bool)), this, SLOT(favoritedChanged(bool)));
        action->deleteLater();
    }
    if (tasks.isEmpty()) {
        setLoading(false);
    } else {
        tasks.takeFirst()->exec();
    }
}


Favorite::Favorite(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

bool Favorite::loading() const
{
    return d->loading;
}

const QString &Favorite::id() const
{
    return d->id;
}

void Favorite::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

bool Favorite::favorited() const
{
    return d->favorited;
}

void Favorite::setFavorited(bool favorited)
{
    if (d->favorited == favorited) return;
    d->favorited = favorited;
    emit favoritedChanged(favorited);
}

#include "favorite.moc"
