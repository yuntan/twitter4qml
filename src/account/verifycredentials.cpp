#include "verifycredentials.h"

#include "../tools/datamanager.h"

#include <QtCore/QMetaProperty>

class VerifyCredentials::Private : public QObject
{
    Q_OBJECT
public:
    Private(VerifyCredentials *parent);

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

private:
    VerifyCredentials *q;
};

VerifyCredentials::Private::Private(VerifyCredentials *parent)
    : QObject(parent)
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
    , q(parent)
{
}

VerifyCredentials::VerifyCredentials(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private(this))
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

bool VerifyCredentials::contributorsEnabled() const
{
    return d->contributorsEnabled;
}

void VerifyCredentials::setContributorsEnabled(bool contributorsEnabled)
{
    if (d->contributorsEnabled == contributorsEnabled) return;
    d->contributorsEnabled = contributorsEnabled;
    emit contributorsEnabledChanged(contributorsEnabled);
}

const QString &VerifyCredentials::createdAt() const
{
    return d->createdAt;
}

void VerifyCredentials::setCreatedAt(const QString &createdAt)
{
    if (d->createdAt == createdAt) return;
    d->createdAt = createdAt;
    emit createdAtChanged(createdAt);
}

const QString &VerifyCredentials::description() const
{
    return d->description;
}

void VerifyCredentials::setDescription(const QString &description)
{
    if (d->description == description) return;
    d->description = description;
    emit descriptionChanged(description);
}

int VerifyCredentials::favouritesCount() const
{
    return d->favouritesCount;
}

void VerifyCredentials::setFavouritesCount(int favouritesCount)
{
    if (d->favouritesCount == favouritesCount) return;
    d->favouritesCount = favouritesCount;
    emit favouritesCountChanged(favouritesCount);
}

bool VerifyCredentials::followRequestSent() const
{
    return d->followRequestSent;
}

void VerifyCredentials::setFollowRequestSent(bool followRequestSent)
{
    if (d->followRequestSent == followRequestSent) return;
    d->followRequestSent = followRequestSent;
    emit followRequestSentChanged(followRequestSent);
}

int VerifyCredentials::followersCount() const
{
    return d->followersCount;
}

void VerifyCredentials::setFollowersCount(int followersCount)
{
    if (d->followersCount == followersCount) return;
    d->followersCount = followersCount;
    emit followersCountChanged(followersCount);
}

bool VerifyCredentials::following() const
{
    return d->following;
}

void VerifyCredentials::setFollowing(bool following)
{
    if (d->following == following) return;
    d->following = following;
    emit followingChanged(following);
}

int VerifyCredentials::friendsCount() const
{
    return d->friendsCount;
}

void VerifyCredentials::setFriendsCount(int friendsCount)
{
    if (d->friendsCount == friendsCount) return;
    d->friendsCount = friendsCount;
    emit friendsCountChanged(friendsCount);
}

bool VerifyCredentials::geoEnabled() const
{
    return d->geoEnabled;
}

void VerifyCredentials::setGeoEnabled(bool geoEnabled)
{
    if (d->geoEnabled == geoEnabled) return;
    d->geoEnabled = geoEnabled;
    emit geoEnabledChanged(geoEnabled);
}

const QString &VerifyCredentials::idStr() const
{
    return d->idStr;
}

void VerifyCredentials::setIdStr(const QString &idStr)
{
    if (d->idStr == idStr) return;
    d->idStr = idStr;
    emit idStrChanged(idStr);
}

bool VerifyCredentials::isTranslator() const
{
    return d->isTranslator;
}

void VerifyCredentials::setIsTranslator(bool isTranslator)
{
    if (d->isTranslator == isTranslator) return;
    d->isTranslator = isTranslator;
    emit isTranslatorChanged(isTranslator);
}

const QString &VerifyCredentials::lang() const
{
    return d->lang;
}

void VerifyCredentials::setLang(const QString &lang)
{
    if (d->lang == lang) return;
    d->lang = lang;
    emit langChanged(lang);
}

int VerifyCredentials::listedCount() const
{
    return d->listedCount;
}

void VerifyCredentials::setListedCount(int listedCount)
{
    if (d->listedCount == listedCount) return;
    d->listedCount = listedCount;
    emit listedCountChanged(listedCount);
}

const QString &VerifyCredentials::location() const
{
    return d->location;
}

void VerifyCredentials::setLocation(const QString &location)
{
    if (d->location == location) return;
    d->location = location;
    emit locationChanged(location);
}

const QString &VerifyCredentials::name() const
{
    return d->name;
}

void VerifyCredentials::setName(const QString &name)
{
    if (d->name == name) return;
    d->name = name;
    emit nameChanged(name);
}

bool VerifyCredentials::notifications() const
{
    return d->notifications;
}

void VerifyCredentials::setNotifications(bool notifications)
{
    if (d->notifications == notifications) return;
    d->notifications = notifications;
    emit notificationsChanged(notifications);
}

const QString &VerifyCredentials::profileBackgroundColor() const
{
    return d->profileBackgroundColor;
}

void VerifyCredentials::setProfileBackgroundColor(const QString &profileBackgroundColor)
{
    if (d->profileBackgroundColor == profileBackgroundColor) return;
    d->profileBackgroundColor = profileBackgroundColor;
    emit profileBackgroundColorChanged(profileBackgroundColor);
}

const QString &VerifyCredentials::profileBackgroundImageUrl() const
{
    return d->profileBackgroundImageUrl;
}

void VerifyCredentials::setProfileBackgroundImageUrl(const QString &profileBackgroundImageUrl)
{
    if (d->profileBackgroundImageUrl == profileBackgroundImageUrl) return;
    d->profileBackgroundImageUrl = profileBackgroundImageUrl;
    emit profileBackgroundImageUrlChanged(profileBackgroundImageUrl);
}

const QString &VerifyCredentials::profileBackgroundImageUrlHttps() const
{
    return d->profileBackgroundImageUrlHttps;
}

void VerifyCredentials::setProfileBackgroundImageUrlHttps(const QString &profileBackgroundImageUrlHttps)
{
    if (d->profileBackgroundImageUrlHttps == profileBackgroundImageUrlHttps) return;
    d->profileBackgroundImageUrlHttps = profileBackgroundImageUrlHttps;
    emit profileBackgroundImageUrlHttpsChanged(profileBackgroundImageUrlHttps);
}

bool VerifyCredentials::profileBackgroundTile() const
{
    return d->profileBackgroundTile;
}

void VerifyCredentials::setProfileBackgroundTile(bool profileBackgroundTile)
{
    if (d->profileBackgroundTile == profileBackgroundTile) return;
    d->profileBackgroundTile = profileBackgroundTile;
    emit profileBackgroundTileChanged(profileBackgroundTile);
}

const QString &VerifyCredentials::profileImageUrl() const
{
    return d->profileImageUrl;
}

void VerifyCredentials::setProfileImageUrl(const QString &profileImageUrl)
{
    if (d->profileImageUrl == profileImageUrl) return;
    d->profileImageUrl = profileImageUrl;
    emit profileImageUrlChanged(profileImageUrl);
}

const QString &VerifyCredentials::profileLinkUrl() const
{
    return d->profileLinkUrl;
}

void VerifyCredentials::setProfileLinkUrl(const QString &profileLinkUrl)
{
    if (d->profileLinkUrl == profileLinkUrl) return;
    d->profileLinkUrl = profileLinkUrl;
    emit profileLinkUrlChanged(profileLinkUrl);
}

const QString &VerifyCredentials::profileSidebarBorderColor() const
{
    return d->profileSidebarBorderColor;
}

void VerifyCredentials::setProfileSidebarBorderColor(const QString &profileSidebarBorderColor)
{
    if (d->profileSidebarBorderColor == profileSidebarBorderColor) return;
    d->profileSidebarBorderColor = profileSidebarBorderColor;
    emit profileSidebarBorderColorChanged(profileSidebarBorderColor);
}

const QString &VerifyCredentials::profileSidebarFillColor() const
{
    return d->profileSidebarFillColor;
}

void VerifyCredentials::setProfileSidebarFillColor(const QString &profileSidebarFillColor)
{
    if (d->profileSidebarFillColor == profileSidebarFillColor) return;
    d->profileSidebarFillColor = profileSidebarFillColor;
    emit profileSidebarFillColorChanged(profileSidebarFillColor);
}

const QString &VerifyCredentials::profileTextColor() const
{
    return d->profileTextColor;
}

void VerifyCredentials::setProfileTextColor(const QString &profileTextColor)
{
    if (d->profileTextColor == profileTextColor) return;
    d->profileTextColor = profileTextColor;
    emit profileTextColorChanged(profileTextColor);
}

const QString &VerifyCredentials::profileUseBackgroundImage() const
{
    return d->profileUseBackgroundImage;
}

void VerifyCredentials::setProfileUseBackgroundImage(const QString &profileUseBackgroundImage)
{
    if (d->profileUseBackgroundImage == profileUseBackgroundImage) return;
    d->profileUseBackgroundImage = profileUseBackgroundImage;
    emit profileUseBackgroundImageChanged(profileUseBackgroundImage);
}

bool VerifyCredentials::isProtected() const
{
    return d->isProtected;
}

void VerifyCredentials::setProtected(bool isProtected)
{
    if (d->isProtected == isProtected) return;
    d->isProtected = isProtected;
    emit protectedChanged(isProtected);
}

const QString &VerifyCredentials::screenName() const
{
    return d->screenName;
}

void VerifyCredentials::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

bool VerifyCredentials::showAllInlineMedia() const
{
    return d->showAllInlineMedia;
}

void VerifyCredentials::setShowAllInlineMedia(bool showAllInlineMedia)
{
    if (d->showAllInlineMedia == showAllInlineMedia) return;
    d->showAllInlineMedia = showAllInlineMedia;
    emit showAllInlineMediaChanged(showAllInlineMedia);
}

int VerifyCredentials::statusesCount() const
{
    return d->statusesCount;
}

void VerifyCredentials::setStatusesCount(int statusesCount)
{
    if (d->statusesCount == statusesCount) return;
    d->statusesCount = statusesCount;
    emit statusesCountChanged(statusesCount);
}

const QString &VerifyCredentials::timeZone() const
{
    return d->timeZone;
}

void VerifyCredentials::setTimeZone(const QString &timeZone)
{
    if (d->timeZone == timeZone) return;
    d->timeZone = timeZone;
    emit timeZoneChanged(timeZone);
}

const QString &VerifyCredentials::url() const
{
    return d->url;
}

void VerifyCredentials::setUrl(const QString &url)
{
    if (d->url == url) return;
    d->url = url;
    emit urlChanged(url);
}

int VerifyCredentials::utcOffset() const
{
    return d->utcOffset;
}

void VerifyCredentials::setUtcOffset(int utcOffset)
{
    if (d->utcOffset == utcOffset) return;
    d->utcOffset = utcOffset;
    emit utcOffsetChanged(utcOffset);
}

bool VerifyCredentials::verified() const
{
    return d->verified;
}

void VerifyCredentials::setVerified(bool verified)
{
    if (d->verified == verified) return;
    d->verified = verified;
    emit verifiedChanged(verified);
}

QVariantMap VerifyCredentials::data() const
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

QVariantMap VerifyCredentials::parse(const QVariantMap &verifyCredentials)
{
    QVariantMap ret = verifyCredentials;
    return ret;
}

#include "verifycredentials.moc"
