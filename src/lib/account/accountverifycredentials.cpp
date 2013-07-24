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

#include "accountverifycredentials.h"

#include "datamanager.h"

#include <QtCore/QMetaProperty>

class AccountVerifyCredentials::Private : public QObject
{
    Q_OBJECT
public:
    Private(AccountVerifyCredentials *parent);

    bool loading;

private slots:
    void dataAdded(DataManager::DataType type, const QString &key, const QVariantMap &value);
    void dataAboutToBeRemoved(DataManager::DataType type, const QString &key, const QVariantMap &value);
//    void dataChanged(DataManager::DataType type, const QString &key, const QVariantMap &value);

private:
    AccountVerifyCredentials *q;
};

AccountVerifyCredentials::Private::Private(AccountVerifyCredentials *parent)
    : QObject(parent)
    , q(parent)
{
    connect(DataManager::instance(), SIGNAL(dataAdded(DataManager::DataType,QString,QVariantMap)), this, SLOT(dataAdded(DataManager::DataType,QString,QVariantMap)));
    connect(DataManager::instance(), SIGNAL(dataAboutToBeRemoved(DataManager::DataType,QString,QVariantMap)), this, SLOT(dataAboutToBeRemoved(DataManager::DataType,QString,QVariantMap)));
//    connect(DataManager::instance(), SIGNAL(dataChanged(DataManager::DataType,QString,QVariantMap)), this, SLOT(dataChanged(DataManager::DataType,QString,QVariantMap)));
}

void AccountVerifyCredentials::Private::dataAdded(DataManager::DataType type, const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (type != DataManager::StatusData) return;
    if (value.value("user").toMap().value("id_str") == q->id_str()) {
        q->statuses_count(q->statuses_count() + 1);
    }
}

void AccountVerifyCredentials::Private::dataAboutToBeRemoved(DataManager::DataType type, const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (type != DataManager::StatusData) return;
    if (value.value("user").toMap().value("id_str") == q->id_str()) {
        q->statuses_count(q->statuses_count() - 1);
    }
}

//void AccountVerifyCredentials::Private::dataChanged(DataManager::DataType type, const QString &key, const QVariantMap &value)
//{
//    Q_UNUSED(key)
//    if (type != DataManager::StatusData) return;
//    if (value.value("favorited").toBool()) {
//    }
//}

AccountVerifyCredentials::AccountVerifyCredentials(QObject *parent)
    : AbstractTwitterAction(parent)
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
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

QVariantMap AccountVerifyCredentials::data() const
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

QVariantMap AccountVerifyCredentials::parse(const QVariantMap &accountVerifyCredentials)
{
    QVariantMap ret = accountVerifyCredentials;
    return ret;
}

#include "accountverifycredentials.moc"
