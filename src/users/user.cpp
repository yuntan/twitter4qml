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

#include "user.h"
#include "showuser.h"
#include "../friendships/createfriendship.h"
#include "../friendships/destroyfriendship.h"
#include "../blocks/createblock.h"
#include "../blocks/destroyblock.h"
#include "../blocks/blockexists.h"
#include "../blocks/reportforspam.h"

#include "../tools/datamanager.h"

#include <QtCore/QMetaProperty>

class User::Private : public QObject
{
    Q_OBJECT
public:
    Private(User *parent);

    bool loading;
    bool contributorsEnabled;
    QString createdAt;
    QString description;
    int favouritesCount;
    bool followRequestSent;
    int followersCount;
    bool following;
    int friendsCount;
    bool geoEnabled;
    QString idStr;
    bool isTranslator;
    QString lang;
    int listedCount;
    QString location;
    QString name;
    bool notifications;
    QString profileBackgroundColor;
    QString profileBackgroundImageUrl;
    QString profileBackgroundImageUrlHttps;
    bool profileBackgroundTile;
    QString profileImageUrl;
    QString profileLinkUrl;
    QString profileSidebarBorderColor;
    QString profileSidebarFillColor;
    QString profileTextColor;
    QString profileUseBackgroundImage;
    bool isProtected;
    QString screenName;
    bool showAllInlineMedia;
    int statusesCount;
    QString timeZone;
    QString url;
    int utcOffset;
    bool verified;
    bool blocking;

    void follow();
    void unfollow();
    void block();
    void unblock();
    void reportForSpam();

private slots:
    void setLoading(bool loading);
    void idStrChanged(const QString &idStr);
    void screenNameChanged(const QString &screenName);
    void dataChanged(const QVariant &data);
    void clear();

private:
    User *q;
    QList<AbstractTwitterAction *> tasks;
};

User::Private::Private(User *parent)
    : QObject(parent)
    , loading(false)
    , contributorsEnabled(false)
    , favouritesCount(0)
    , followRequestSent(false)
    , followersCount(0)
    , following(false)
    , friendsCount(0)
    , geoEnabled(false)
    , isTranslator(false)
    , listedCount(0)
    , notifications(false)
    , profileBackgroundTile(false)
    , isProtected(false)
    , showAllInlineMedia(false)
    , statusesCount(0)
    , utcOffset(0)
    , verified(false)
    , blocking(false)
    , q(parent)
{
    connect(q, SIGNAL(idStrChanged(QString)), this, SLOT(idStrChanged(QString)), Qt::QueuedConnection);
    connect(q, SIGNAL(screenNameChanged(QString)), this, SLOT(screenNameChanged(QString)), Qt::QueuedConnection);
}

void User::Private::setLoading(bool l)
{
    if (loading == l) return;
    loading = l;
    emit q->loadingChanged(l);
}

void User::Private::idStrChanged(const QString &idStr)
{
    if (q->loading()) return;
//    if (!screenName.isEmpty()) return;
//    clear();
//    screenName.clear();

    DEBUG() << idStr;
    if (idStr.isEmpty()) {
    } else {
        {
            ShowUser *action = new ShowUser(this);
            action->setUserId(idStr);
            connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
            if (loading) {
                tasks.append(action);
            } else {
                setLoading(true);
                action->exec();
            }
        }
        {
            BlockExists *action = new BlockExists(this);
            action->setUserId(idStr);
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

void User::Private::screenNameChanged(const QString &screenName)
{
    if (q->loading()) return;
//    if (!idStr.isEmpty()) return;
//    clear();
//    idStr.clear();

    DEBUG() << screenName;
    if (screenName.isEmpty()) {
    } else {
        {
            ShowUser *action = new ShowUser(this);
            action->setScreenName(screenName);
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
    contributorsEnabled = false;
    createdAt.clear();
    description.clear();
    favouritesCount = 0;
    followRequestSent = false;
    followersCount = 0;
    following = false;
    friendsCount = 0;
    geoEnabled = false;
    isTranslator = false;
    lang.clear();
    listedCount = 0;
    location.clear();
    name.clear();
    notifications = false;
    profileBackgroundColor.clear();
    profileBackgroundImageUrl.clear();
    profileBackgroundImageUrlHttps.clear();
    profileBackgroundTile = false;
    profileImageUrl.clear();
    profileLinkUrl.clear();
    profileSidebarBorderColor.clear();
    profileSidebarFillColor.clear();
    profileTextColor.clear();
    profileUseBackgroundImage.clear();
    isProtected = false;
    showAllInlineMedia = false;
    statusesCount = 0;
    timeZone.clear();
    url.clear();
    utcOffset = 0;
    verified = false;
    blocking = false;
}

void User::Private::follow()
{
    CreateFriendship *action = new CreateFriendship(this);
    action->setUserId(idStr);
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
    action->setUserId(idStr);
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
    action->setUserId(idStr);
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
    action->setUserId(idStr);
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
    action->setUserId(idStr);
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
                q->setBlocking(true);
            } else if (qobject_cast<DestroyBlock *>(action)) {
                q->setBlocking(false);
            } else if (qobject_cast<BlockExists *>(action)) {
                q->setBlocking(map.contains("id_str"));
            } else if (qobject_cast<ReportForSpam *>(action)) {
                q->setBlocking(true);
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
            DataManager::instance()->addData(DataManager::UserData, q->idStr(), user);
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

bool User::contributorsEnabled() const
{
    return d->contributorsEnabled;
}

void User::setContributorsEnabled(bool contributorsEnabled)
{
    if (d->contributorsEnabled == contributorsEnabled) return;
    d->contributorsEnabled = contributorsEnabled;
    emit contributorsEnabledChanged(contributorsEnabled);
}

const QString &User::createdAt() const
{
    return d->createdAt;
}

void User::setCreatedAt(const QString &createdAt)
{
    if (d->createdAt == createdAt) return;
    d->createdAt = createdAt;
    emit createdAtChanged(createdAt);
}

const QString &User::description() const
{
    return d->description;
}

void User::setDescription(const QString &description)
{
    if (d->description == description) return;
    d->description = description;
    emit descriptionChanged(description);
}

int User::favouritesCount() const
{
    return d->favouritesCount;
}

void User::setFavouritesCount(int favouritesCount)
{
    if (d->favouritesCount == favouritesCount) return;
    d->favouritesCount = favouritesCount;
    emit favouritesCountChanged(favouritesCount);
}

bool User::followRequestSent() const
{
    return d->followRequestSent;
}

void User::setFollowRequestSent(bool followRequestSent)
{
    if (d->followRequestSent == followRequestSent) return;
    d->followRequestSent = followRequestSent;
    emit followRequestSentChanged(followRequestSent);
}

int User::followersCount() const
{
    return d->followersCount;
}

void User::setFollowersCount(int followersCount)
{
    if (d->followersCount == followersCount) return;
    d->followersCount = followersCount;
    emit followersCountChanged(followersCount);
}

bool User::following() const
{
    return d->following;
}

void User::setFollowing(bool following)
{
    if (d->following == following) return;
    d->following = following;
    emit followingChanged(following);
}

int User::friendsCount() const
{
    return d->friendsCount;
}

void User::setFriendsCount(int friendsCount)
{
    if (d->friendsCount == friendsCount) return;
    d->friendsCount = friendsCount;
    emit friendsCountChanged(friendsCount);
}

bool User::geoEnabled() const
{
    return d->geoEnabled;
}

void User::setGeoEnabled(bool geoEnabled)
{
    if (d->geoEnabled == geoEnabled) return;
    d->geoEnabled = geoEnabled;
    emit geoEnabledChanged(geoEnabled);
}

const QString &User::idStr() const
{
    return d->idStr;
}

void User::setIdStr(const QString &idStr)
{
    if (d->idStr == idStr) return;
    DEBUG() << d->idStr << idStr;
    d->idStr = idStr;
    emit idStrChanged(idStr);
}

bool User::isTranslator() const
{
    return d->isTranslator;
}

void User::setIsTranslator(bool isTranslator)
{
    if (d->isTranslator == isTranslator) return;
    d->isTranslator = isTranslator;
    emit isTranslatorChanged(isTranslator);
}

const QString &User::lang() const
{
    return d->lang;
}

void User::setLang(const QString &lang)
{
    if (d->lang == lang) return;
    d->lang = lang;
    emit langChanged(lang);
}

int User::listedCount() const
{
    return d->listedCount;
}

void User::setListedCount(int listedCount)
{
    if (d->listedCount == listedCount) return;
    d->listedCount = listedCount;
    emit listedCountChanged(listedCount);
}

const QString &User::location() const
{
    return d->location;
}

void User::setLocation(const QString &location)
{
    if (d->location == location) return;
    d->location = location;
    emit locationChanged(location);
}

const QString &User::name() const
{
    return d->name;
}

void User::setName(const QString &name)
{
    if (d->name == name) return;
    d->name = name;
    emit nameChanged(name);
}

bool User::notifications() const
{
    return d->notifications;
}

void User::setNotifications(bool notifications)
{
    if (d->notifications == notifications) return;
    d->notifications = notifications;
    emit notificationsChanged(notifications);
}

const QString &User::profileBackgroundColor() const
{
    return d->profileBackgroundColor;
}

void User::setProfileBackgroundColor(const QString &profileBackgroundColor)
{
    if (d->profileBackgroundColor == profileBackgroundColor) return;
    d->profileBackgroundColor = profileBackgroundColor;
    emit profileBackgroundColorChanged(profileBackgroundColor);
}

const QString &User::profileBackgroundImageUrl() const
{
    return d->profileBackgroundImageUrl;
}

void User::setProfileBackgroundImageUrl(const QString &profileBackgroundImageUrl)
{
    if (d->profileBackgroundImageUrl == profileBackgroundImageUrl) return;
    d->profileBackgroundImageUrl = profileBackgroundImageUrl;
    emit profileBackgroundImageUrlChanged(profileBackgroundImageUrl);
}

const QString &User::profileBackgroundImageUrlHttps() const
{
    return d->profileBackgroundImageUrlHttps;
}

void User::setProfileBackgroundImageUrlHttps(const QString &profileBackgroundImageUrlHttps)
{
    if (d->profileBackgroundImageUrlHttps == profileBackgroundImageUrlHttps) return;
    d->profileBackgroundImageUrlHttps = profileBackgroundImageUrlHttps;
    emit profileBackgroundImageUrlHttpsChanged(profileBackgroundImageUrlHttps);
}

bool User::profileBackgroundTile() const
{
    return d->profileBackgroundTile;
}

void User::setProfileBackgroundTile(bool profileBackgroundTile)
{
    if (d->profileBackgroundTile == profileBackgroundTile) return;
    d->profileBackgroundTile = profileBackgroundTile;
    emit profileBackgroundTileChanged(profileBackgroundTile);
}

const QString &User::profileImageUrl() const
{
    return d->profileImageUrl;
}

void User::setProfileImageUrl(const QString &profileImageUrl)
{
    if (d->profileImageUrl == profileImageUrl) return;
    d->profileImageUrl = profileImageUrl;
    emit profileImageUrlChanged(profileImageUrl);
}

const QString &User::profileLinkUrl() const
{
    return d->profileLinkUrl;
}

void User::setProfileLinkUrl(const QString &profileLinkUrl)
{
    if (d->profileLinkUrl == profileLinkUrl) return;
    d->profileLinkUrl = profileLinkUrl;
    emit profileLinkUrlChanged(profileLinkUrl);
}

const QString &User::profileSidebarBorderColor() const
{
    return d->profileSidebarBorderColor;
}

void User::setProfileSidebarBorderColor(const QString &profileSidebarBorderColor)
{
    if (d->profileSidebarBorderColor == profileSidebarBorderColor) return;
    d->profileSidebarBorderColor = profileSidebarBorderColor;
    emit profileSidebarBorderColorChanged(profileSidebarBorderColor);
}

const QString &User::profileSidebarFillColor() const
{
    return d->profileSidebarFillColor;
}

void User::setProfileSidebarFillColor(const QString &profileSidebarFillColor)
{
    if (d->profileSidebarFillColor == profileSidebarFillColor) return;
    d->profileSidebarFillColor = profileSidebarFillColor;
    emit profileSidebarFillColorChanged(profileSidebarFillColor);
}

const QString &User::profileTextColor() const
{
    return d->profileTextColor;
}

void User::setProfileTextColor(const QString &profileTextColor)
{
    if (d->profileTextColor == profileTextColor) return;
    d->profileTextColor = profileTextColor;
    emit profileTextColorChanged(profileTextColor);
}

const QString &User::profileUseBackgroundImage() const
{
    return d->profileUseBackgroundImage;
}

void User::setProfileUseBackgroundImage(const QString &profileUseBackgroundImage)
{
    if (d->profileUseBackgroundImage == profileUseBackgroundImage) return;
    d->profileUseBackgroundImage = profileUseBackgroundImage;
    emit profileUseBackgroundImageChanged(profileUseBackgroundImage);
}

bool User::isProtected() const
{
    return d->isProtected;
}

void User::setProtected(bool isProtected)
{
    if (d->isProtected == isProtected) return;
    d->isProtected = isProtected;
    emit protectedChanged(isProtected);
}

const QString &User::screenName() const
{
    return d->screenName;
}

void User::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

bool User::showAllInlineMedia() const
{
    return d->showAllInlineMedia;
}

void User::setShowAllInlineMedia(bool showAllInlineMedia)
{
    if (d->showAllInlineMedia == showAllInlineMedia) return;
    d->showAllInlineMedia = showAllInlineMedia;
    emit showAllInlineMediaChanged(showAllInlineMedia);
}

int User::statusesCount() const
{
    return d->statusesCount;
}

void User::setStatusesCount(int statusesCount)
{
    if (d->statusesCount == statusesCount) return;
    d->statusesCount = statusesCount;
    emit statusesCountChanged(statusesCount);
}

const QString &User::timeZone() const
{
    return d->timeZone;
}

void User::setTimeZone(const QString &timeZone)
{
    if (d->timeZone == timeZone) return;
    d->timeZone = timeZone;
    emit timeZoneChanged(timeZone);
}

const QString &User::url() const
{
    return d->url;
}

void User::setUrl(const QString &url)
{
    if (d->url == url) return;
    d->url = url;
    emit urlChanged(url);
}

int User::utcOffset() const
{
    return d->utcOffset;
}

void User::setUtcOffset(int utcOffset)
{
    if (d->utcOffset == utcOffset) return;
    d->utcOffset = utcOffset;
    emit utcOffsetChanged(utcOffset);
}

bool User::verified() const
{
    return d->verified;
}

void User::setVerified(bool verified)
{
    if (d->verified == verified) return;
    d->verified = verified;
    emit verifiedChanged(verified);
}

bool User::blocking() const
{
    return d->blocking;
}

void User::setBlocking(bool blocking)
{
    if (d->blocking == blocking) return;
    d->blocking = blocking;
    emit blockingChanged(blocking);
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
