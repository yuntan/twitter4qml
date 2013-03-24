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

#include "user.h"
#include "showuser.h"
#include "../friendships/createfriendship.h"
#include "../friendships/destroyfriendship.h"
#include "../blocks/createblock.h"
#include "../blocks/destroyblock.h"
#include "../blocks/reportforspam.h"

#include "datamanager.h"

#include <QtCore/QMetaProperty>

class User::Private : public QObject
{
    Q_OBJECT
public:
    Private(User *parent);

    bool loading;
    bool contributors_enabled;
    QString created_at;
    QString description;
    int favourites_count;
    bool follow_request_sent;
    int followers_count;
    bool following;
    int friends_count;
    bool geo_enabled;
    QString id_str;
    bool is_translator;
    QString lang;
    int listed_count;
    QString location;
    QString name;
    bool notifications;
    QString profile_background_color;
    QString profile_background_image_url;
    QString profile_background_image_url_https;
    bool profile_background_tile;
    QString profile_image_url;
    QString profile_link_url;
    QString profile_sidebar_border_color;
    QString profile_sidebar_fill_color;
    QString profile_text_color;
    QString profile_use_background_image;
    bool _protected;
    QString screen_name;
    bool show_all_inline_media;
    int statuses_count;
    QString time_zone;
    QString url;
    int utc_offset;
    bool verified;
    bool blocking;

    void follow();
    void unfollow();
    void block();
    void unblock();
    void reportForSpam();

private slots:
    void setLoading(bool loading);
    void id_strChanged(const QString &id_str);
    void screen_nameChanged(const QString &screen_name);
    void dataChanged(const QVariant &data);
    void clear();

private:
    User *q;
    QList<AbstractTwitterAction *> tasks;
};

User::Private::Private(User *parent)
    : QObject(parent)
    , loading(false)
    , contributors_enabled(false)
    , favourites_count(0)
    , follow_request_sent(false)
    , followers_count(0)
    , following(false)
    , friends_count(0)
    , geo_enabled(false)
    , is_translator(false)
    , listed_count(0)
    , notifications(false)
    , profile_background_tile(false)
    , _protected(false)
    , show_all_inline_media(false)
    , statuses_count(0)
    , utc_offset(0)
    , verified(false)
    , blocking(false)
    , q(parent)
{
    connect(q, SIGNAL(id_strChanged(QString)), this, SLOT(id_strChanged(QString)), Qt::QueuedConnection);
    connect(q, SIGNAL(screen_nameChanged(QString)), this, SLOT(screen_nameChanged(QString)), Qt::QueuedConnection);
}

void User::Private::setLoading(bool l)
{
    if (loading == l) return;
    loading = l;
    emit q->loadingChanged(l);
}

void User::Private::id_strChanged(const QString &id_str)
{
    if (q->loading()) return;
//    if (!screen_name.isEmpty()) return;
//    clear();
//    screen_name.clear();

    DEBUG() << id_str;
    if (id_str.isEmpty()) {
    } else {
        {
            ShowUser *action = new ShowUser(this);
            action->user_id(id_str);
            connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
            if (loading) {
                tasks.append(action);
            } else {
                setLoading(true);
                action->exec();
            }
        }
    }
}

void User::Private::screen_nameChanged(const QString &screen_name)
{
    if (q->loading()) return;
//    if (!id_str.isEmpty()) return;
//    clear();
//    id_str.clear();

    DEBUG() << screen_name;
    if (screen_name.isEmpty()) {
    } else {
        {
            ShowUser *action = new ShowUser(this);
            action->screen_name(screen_name);
            connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
            if (loading) {
                tasks.append(action);
            } else {
                setLoading(true);
                action->exec();
            }
        }
    }
}

void User::Private::clear()
{
    contributors_enabled = false;
    created_at.clear();
    description.clear();
    favourites_count = 0;
    follow_request_sent = false;
    followers_count = 0;
    following = false;
    friends_count = 0;
    geo_enabled = false;
    is_translator = false;
    lang.clear();
    listed_count = 0;
    location.clear();
    name.clear();
    notifications = false;
    profile_background_color.clear();
    profile_background_image_url.clear();
    profile_background_image_url_https.clear();
    profile_background_tile = false;
    profile_image_url.clear();
    profile_link_url.clear();
    profile_sidebar_border_color.clear();
    profile_sidebar_fill_color.clear();
    profile_text_color.clear();
    profile_use_background_image.clear();
    _protected = false;
    show_all_inline_media = false;
    statuses_count = 0;
    time_zone.clear();
    url.clear();
    utc_offset = 0;
    verified = false;
    blocking = false;
}

void User::Private::follow()
{
    CreateFriendship *action = new CreateFriendship(this);
    action->user_id(id_str);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void User::Private::unfollow()
{
    DestroyFriendship *action = new DestroyFriendship(this);
    action->user_id(id_str);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void User::Private::block()
{
    CreateBlock *action = new CreateBlock(this);
    action->user_id(id_str);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void User::Private::unblock()
{
    DestroyBlock *action = new DestroyBlock(this);
    action->user_id(id_str);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void User::Private::reportForSpam()
{
    ReportForSpam *action = new ReportForSpam(this);
    action->user_id(id_str);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void User::Private::dataChanged(const QVariant &data)
{
    QVariantMap map = data.toMap();
//    DEBUG() << data << sender();
    AbstractTwitterAction *action = qobject_cast<AbstractTwitterAction *>(sender());
    if (action) {
        if (qobject_cast<AbstractBlockAction *>(action)) {
            if (qobject_cast<CreateBlock *>(action)) {
                q->blocking(true);
            } else if (qobject_cast<DestroyBlock *>(action)) {
                q->blocking(false);
            } else if (qobject_cast<ReportForSpam *>(action)) {
                q->blocking(true);
            }
        } else {
            QVariantMap user = User::parse(map);
            const QMetaObject *mo = q->metaObject();
            for (int i = 0; i < mo->propertyCount(); i++) {
                QMetaProperty prop = mo->property(i);
                if (!prop.isDesignable()) continue;
                const char *key = prop.name();
                if (user.contains(key)) {
                    if (QLatin1String("following") == key) {
                        if (qobject_cast<AbstractFriendshipAction *>(sender())) {
                            q->setProperty(key, !user.value(key).toBool());
                        } else {
                            q->setProperty(key, user.value(key));
                        }
                    } else {
                        q->setProperty(key, user.value(key));
                    }
                } else {
                    q->setProperty(key, QVariant());
                }
            }
            DataManager::instance()->addData(DataManager::UserData, q->id_str(), user);
            emit q->dataChanged();
        }
        action->deleteLater();
    }
    if (tasks.isEmpty()) {
        setLoading(false);
    } else {
        tasks.takeFirst()->exec();
    }
}


User::User(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

void User::follow()
{
    d->follow();
}

void User::unfollow()
{
    d->unfollow();
}

void User::block()
{
    d->block();
}

void User::unblock()
{
    d->unblock();
}

void User::reportForSpam()
{
    d->reportForSpam();
}

bool User::loading() const
{
    return d->loading;
}

QVariantMap User::data() const
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

void User::debug() const
{
    const QMetaObject *mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty prop = mo->property(i);
        if (!prop.isDesignable()) continue;
        const char *key = prop.name();
        DEBUG() << key << property(key);
    }
}

QVariantMap User::parse(const QVariantMap &user)
{
    QVariantMap ret = user;
    return ret;
}

#include "user.moc"
