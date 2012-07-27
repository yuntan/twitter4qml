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
