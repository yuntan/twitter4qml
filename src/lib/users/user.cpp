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
#include "../friendships/createfriendships.h"
#include "../friendships/destroyfriendships.h"
#include "../blocks/blockscreate.h"
#include "../blocks/blocksdestroy.h"
#include "../blocks/reportforspam.h"

#include "datamanager.h"

#include <QtCore/QMetaProperty>

class User::Private : public QObject
{
    Q_OBJECT
public:
    Private(User *parent);

    bool loading;
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
    if (q->isLoading()) return;
//    if (!screen_name.isEmpty()) return;
//    clear();
//    screen_name.clear();

    if (id_str.isEmpty()) {
    } else if (q->screen_name().isEmpty()) {
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

void User::Private::screen_nameChanged(const QString &screen_name)
{
    if (q->isLoading()) return;
//    if (!id_str.isEmpty()) return;
//    clear();
//    id_str.clear();

    if (screen_name.isEmpty()) {
    } else if (q->id_str().isEmpty()) {
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

void User::Private::clear()
{
    q->m_contributors_enabled = false;
    q->m_created_at.clear();
    q->m_description.clear();
    q->m_favourites_count = 0;
    q->m_follow_request_sent = false;
    q->m_followers_count = 0;
    q->m_following = false;
    q->m_friends_count = 0;
    q->m_geo_enabled = false;
    q->m_is_translator = false;
    q->m_lang.clear();
    q->m_listed_count = 0;
    q->m_location.clear();
    q->m_name.clear();
    q->m_notifications = false;
    q->m_profile_background_color.clear();
    q->m_profile_background_image_url.clear();
    q->m_profile_background_image_url_https.clear();
    q->m_profile_background_tile = false;
    q->m_profile_image_url.clear();
    q->m_profile_link_url.clear();
    q->m_profile_sidebar_border_color.clear();
    q->m_profile_sidebar_fill_color.clear();
    q->m_profile_text_color.clear();
    q->m_profile_use_background_image.clear();
    q->m__protected = false;
    q->m_show_all_inline_media = false;
    q->m_statuses_count = 0;
    q->m_time_zone.clear();
    q->m_url.clear();
    q->m_utc_offset = 0;
    q->m_verified = false;
    q->m_blocking = false;
}

void User::Private::follow()
{
    CreateFriendships *action = new CreateFriendships(this);
    action->user_id(q->id_str());
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
    DestroyFriendships *action = new DestroyFriendships(this);
    action->user_id(q->id_str());
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
    BlocksCreate *action = new BlocksCreate(this);
    action->user_id(q->id_str());
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
    BlocksDestroy *action = new BlocksDestroy(this);
    action->user_id(q->id_str());
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
    action->user_id(q->id_str());
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
    AbstractTwitterAction *action = qobject_cast<AbstractTwitterAction *>(sender());
    if (action) {
        if (qobject_cast<AbstractBlocksAction *>(action)) {
            if (qobject_cast<BlocksCreate *>(action)) {
                q->blocking(true);
            } else if (qobject_cast<BlocksDestroy *>(action)) {
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
                        if (qobject_cast<CreateFriendships *>(sender())) {
                            q->setProperty(key, true);
                        } else if (qobject_cast<DestroyFriendships *>(sender())) {
                                q->setProperty(key, false);
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
    , m_contributors_enabled(false)
    , m_favourites_count(0)
    , m_follow_request_sent(false)
    , m_followers_count(0)
    , m_following(false)
    , m_friends_count(0)
    , m_geo_enabled(false)
    , m_is_translator(false)
    , m_listed_count(0)
    , m_notifications(false)
    , m_profile_background_tile(false)
    , m__protected(false)
    , m_show_all_inline_media(false)
    , m_statuses_count(0)
    , m_utc_offset(0)
    , m_verified(false)
    , m_blocking(false)
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

bool User::isLoading() const
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
