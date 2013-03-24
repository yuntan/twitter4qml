/* Copyright (c) 2012-2013 Twitter4QML Project.
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

#include "list.h"
#include "showlist.h"
#include "createlist.h"
#include "updatelist.h"
#include "destroylist.h"
#include "subscribelist.h"
#include "unsubscribelist.h"

#include "datamanager.h"

#include <QtCore/QMetaProperty>
#include <QtCore/QPointF>

class List::Private : public QObject
{
    Q_OBJECT
public:
    Private(List *parent);

    bool loading;
    QString created_at;
    QString description;
    bool following;
    QString fullName;
    QString id_str;
    int memberCount;
    QString mode;
    QString name;
    QString slug;
    int subscriberCount;
    QString uri;
    QVariantMap user;

    void create(const QVariantMap &parameters);
    void update(const QVariantMap &parameters);
    void destroy();
    void subscribe();
    void unsubscribe();

private slots:
    void setLoading(bool loading);
    void id_strChanged(const QString &id_str);
    void dataChanged(const QVariant &data);

private:
    List *q;
    QList<AbstractTwitterAction *> tasks;
};

List::Private::Private(List *parent)
    : QObject(parent)
    , loading(false)
    , following(false)
    , memberCount(0)
    , subscriberCount(0)
    , q(parent)
{
    connect(q, SIGNAL(id_strChanged(QString)), this, SLOT(id_strChanged(QString)));
}

void List::Private::setLoading(bool l)
{
    if (loading == l) return;
    loading = l;
    emit q->loadingChanged(l);
}

void List::Private::id_strChanged(const QString &id)
{
    q->created_at(QString());
    q->description(QString());
    q->following(false);
    q->setFullName(QString());
    q->setMemberCount(0);
    q->mode(QString());
    q->name(QString());
    q->slug(QString());
    q->setSubscriberCount(0);
    q->setUri(QString());
    q->user(QVariantMap());

    DEBUG() << id;
    if (id.isEmpty()) {
    } else {
        ShowList *action = new ShowList(this);
        action->list_id(id);
        connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
        if (loading) {
            tasks.append(action);
        } else {
            setLoading(true);
            action->exec();
        }
    }
}

void List::Private::create(const QVariantMap &parameters)
{
    CreateList *action = new CreateList(this);
    action->description(parameters.value("description").toString());
    action->mode(parameters.value("mode").toString());
    action->name(parameters.value("name").toString());
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void List::Private::update(const QVariantMap &parameters)
{
    UpdateList *action = new UpdateList(this);
    action->list_id(id_str);
    action->description(parameters.value("description").toString());
    action->mode(parameters.value("mode").toString());
    action->name(parameters.value("name").toString());
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void List::Private::destroy()
{
    DestroyList *action = new DestroyList(this);
    action->list_id(id_str);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void List::Private::subscribe()
{
    SubscribeList *action = new SubscribeList(this);
    action->list_id(id_str);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void List::Private::unsubscribe()
{
    UnsubscribeList *action = new UnsubscribeList(this);
    action->list_id(id_str);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void List::Private::dataChanged(const QVariant &data)
{
//    DEBUG() << data << sender();
    AbstractTwitterAction *action = qobject_cast<AbstractTwitterAction *>(sender());
    if (action) {
        QVariantMap list = List::parse(data.toMap());
        const QMetaObject *mo = q->metaObject();
        for (int i = 0; i < mo->propertyCount(); i++) {
            QMetaProperty prop = mo->property(i);
            if (!prop.isDesignable()) continue;
            const char *key = prop.name();
            if (list.contains(key)) {
                if (QLatin1String("following") == key) {
//                    if (qobject_cast<AbstractFriendshipAction *>(sender())) {
//                        q->setProperty(key, !list.value(key).toBool());
//                    } else {
                        q->setProperty(key, list.value(key));
//                    }
                } else {
                    q->setProperty(key, list.value(key));
                }
            } else {
                q->setProperty(key, QVariant());
            }
        }
        DataManager::instance()->addData(DataManager::ListData, q->id_str(), list);
        emit q->dataChanged();
        action->deleteLater();
    }
    if (tasks.isEmpty()) {
        setLoading(false);
    } else {
        tasks.takeFirst()->exec();
    }
}


List::List(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

void List::createList(QVariantMap parameters)
{
    d->create(parameters);
}

void List::updateList(QVariantMap parameters)
{
    d->update(parameters);
}


void List::destroyList()
{
    d->destroy();
}

void List::subscribe()
{
    d->subscribe();
}

void List::unsubscribe()
{
    d->unsubscribe();
}

bool List::loading() const
{
    return d->loading;
}

const QString &List::created_at() const
{
    return d->created_at;
}

void List::created_at(const QString &created_at)
{
    if (d->created_at == created_at) return;
    d->created_at = created_at;
    emit created_atChanged(created_at);
}

const QString &List::description() const
{
    return d->description;
}

void List::description(const QString &description)
{
    if (d->description == description) return;
    d->description = description;
    emit descriptionChanged(description);
}

bool List::following() const
{
    return d->following;
}

void List::following(bool following)
{
    if (d->following == following) return;
    d->following = following;
    emit followingChanged(following);
}

const QString &List::fullName() const
{
    return d->fullName;
}

void List::setFullName(const QString &fullName)
{
    if (d->fullName == fullName) return;
    d->fullName = fullName;
    emit fullNameChanged(fullName);
}

const QString &List::id_str() const
{
    return d->id_str;
}

void List::id_str(const QString &id_str)
{
    if (d->id_str == id_str) return;
    DEBUG() << d->id_str << id_str;
    d->id_str = id_str;
    emit id_strChanged(id_str);
}

int List::memberCount() const
{
    return d->memberCount;
}

void List::setMemberCount(int memberCount)
{
    if (d->memberCount == memberCount) return;
    d->memberCount = memberCount;
    emit memberCountChanged(memberCount);
}

const QString &List::mode() const
{
    return d->mode;
}

void List::mode(const QString &mode)
{
    if (d->mode == mode) return;
    d->mode = mode;
    emit modeChanged(mode);
}

const QString &List::name() const
{
    return d->name;
}

void List::name(const QString &name)
{
    if (d->name == name) return;
    d->name = name;
    emit nameChanged(name);
}

const QString &List::slug() const
{
    return d->slug;
}

void List::slug(const QString &slug)
{
    if (d->slug == slug) return;
    d->slug = slug;
    emit slugChanged(slug);
}

int List::subscriberCount() const
{
    return d->subscriberCount;
}

void List::setSubscriberCount(int subscriberCount)
{
    if (d->subscriberCount == subscriberCount) return;
    d->subscriberCount = subscriberCount;
    emit subscriberCountChanged(subscriberCount);
}

const QString &List::uri() const
{
    return d->uri;
}

void List::setUri(const QString &uri)
{
    if (d->uri == uri) return;
    d->uri = uri;
    emit uriChanged(uri);
}

const QVariantMap &List::user() const
{
    return d->user;
}

void List::user(const QVariantMap &user)
{
    if (d->user == user) return;
    d->user = user;
    emit userChanged(user);
}


QVariantMap List::data() const
{
    QVariantMap ret;
    const QMetaObject *mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty prop = mo->property(i);
        if (!prop.isDesignable()) continue;
        const char *key = prop.name();
        ret.insert(key, property(key));
    }
    return ret;
}

void List::debug() const
{
    const QMetaObject *mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty prop = mo->property(i);
        if (!prop.isDesignable()) continue;
        const char *key = prop.name();
        DEBUG() << key << property(key);
    }
}

QVariantMap List::parse(const QVariantMap &list)
{
    QVariantMap ret = list;
    return ret;
}

#include "list.moc"
