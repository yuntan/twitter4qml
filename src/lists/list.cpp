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

#include "list.h"
#include "showlist.h"
#include "createlist.h"
#include "updatelist.h"
#include "destroylist.h"
#include "subscribelist.h"
#include "unsubscribelist.h"

#include "../tools/datamanager.h"

#include <QtCore/QMetaProperty>
#include <QtCore/QPointF>

class List::Private : public QObject
{
    Q_OBJECT
public:
    Private(List *parent);

    bool loading;
    QString createdAt;
    QString description;
    bool following;
    QString fullName;
    QString idStr;
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
    void idStrChanged(const QString &idStr);
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
    connect(q, SIGNAL(idStrChanged(QString)), this, SLOT(idStrChanged(QString)));
}

void List::Private::setLoading(bool l)
{
    if (loading == l) return;
    loading = l;
    emit q->loadingChanged(l);
}

void List::Private::idStrChanged(const QString &id)
{
    createdAt.clear();
    description.clear();
    following = false;
    fullName.clear();
    memberCount = 0;
    mode.clear();
    name.clear();
    slug.clear();
    subscriberCount = 0;
    uri.clear();
    user.clear();

    DEBUG() << id;
    if (id.isEmpty()) {
    } else {
        ShowList *action = new ShowList(this);
        action->setListId(id);
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
    action->setDescription(parameters.value("description").toString());
    action->setMode(parameters.value("mode").toString());
    action->setName(parameters.value("name").toString());
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
    action->setListId(idStr);
    action->setDescription(parameters.value("description").toString());
    action->setMode(parameters.value("mode").toString());
    action->setName(parameters.value("name").toString());
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
    action->setListId(idStr);
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
    action->setListId(idStr);
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
    action->setListId(idStr);
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
        DataManager::instance()->addData(DataManager::ListData, q->idStr(), list);
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

const QString &List::createdAt() const
{
    return d->createdAt;
}

void List::setCreatedAt(const QString &createdAt)
{
    if (d->createdAt == createdAt) return;
    d->createdAt = createdAt;
    emit createdAtChanged(createdAt);
}

const QString &List::description() const
{
    return d->description;
}

void List::setDescription(const QString &description)
{
    if (d->description == description) return;
    d->description = description;
    emit descriptionChanged(description);
}

bool List::following() const
{
    return d->following;
}

void List::setFollowing(bool following)
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

const QString &List::idStr() const
{
    return d->idStr;
}

void List::setIdStr(const QString &idStr)
{
    if (d->idStr == idStr) return;
    DEBUG() << d->idStr << idStr;
    d->idStr = idStr;
    emit idStrChanged(idStr);
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

void List::setMode(const QString &mode)
{
    if (d->mode == mode) return;
    d->mode = mode;
    emit modeChanged(mode);
}

const QString &List::name() const
{
    return d->name;
}

void List::setName(const QString &name)
{
    if (d->name == name) return;
    d->name = name;
    emit nameChanged(name);
}

const QString &List::slug() const
{
    return d->slug;
}

void List::setSlug(const QString &slug)
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

void List::setUser(const QVariantMap &user)
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
