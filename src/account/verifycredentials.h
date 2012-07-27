#ifndef VERIFYCREDENTIALS_H
#define VERIFYCREDENTIALS_H

#include "../tools/abstracttwitteraction.h"

class VerifyCredentials : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(bool contributors_enabled READ contributorsEnabled WRITE setContributorsEnabled NOTIFY contributorsEnabledChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString created_at READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged DESIGNABLE false USER true)
    Q_PROPERTY(int favourites_count READ favouritesCount WRITE setFavouritesCount NOTIFY favouritesCountChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool follow_request_sent READ followRequestSent WRITE setFollowRequestSent NOTIFY followRequestSentChanged DESIGNABLE false USER true)
    Q_PROPERTY(int followers_count READ followersCount WRITE setFollowersCount NOTIFY followersCountChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool following READ following WRITE setFollowing NOTIFY followingChanged DESIGNABLE false USER true)
    Q_PROPERTY(int friends_count READ friendsCount WRITE setFriendsCount NOTIFY friendsCountChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool geo_enabled READ geoEnabled WRITE setGeoEnabled NOTIFY geoEnabledChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString id_str READ idStr WRITE setIdStr NOTIFY idStrChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool is_translator READ isTranslator WRITE setIsTranslator NOTIFY isTranslatorChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString lang READ lang WRITE setLang NOTIFY langChanged DESIGNABLE false USER true)
    Q_PROPERTY(int listed_count READ listedCount WRITE setListedCount NOTIFY listedCountChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool notifications READ notifications WRITE setNotifications NOTIFY notificationsChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString profile_background_color READ profileBackgroundColor WRITE setProfileBackgroundColor NOTIFY profileBackgroundColorChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString profile_background_image_url READ profileBackgroundImageUrl WRITE setProfileBackgroundImageUrl NOTIFY profileBackgroundImageUrlChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString profile_background_image_url_https READ profileBackgroundImageUrlHttps WRITE setProfileBackgroundImageUrlHttps NOTIFY profileBackgroundImageUrlHttpsChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool profile_background_tile READ profileBackgroundTile WRITE setProfileBackgroundTile NOTIFY profileBackgroundTileChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString profile_image_url READ profileImageUrl WRITE setProfileImageUrl NOTIFY profileImageUrlChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString profile_link_url READ profileLinkUrl WRITE setProfileLinkUrl NOTIFY profileLinkUrlChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString profile_sidebar_border_color READ profileSidebarBorderColor WRITE setProfileSidebarBorderColor NOTIFY profileSidebarBorderColorChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString profile_sidebar_fill_color READ profileSidebarFillColor WRITE setProfileSidebarFillColor NOTIFY profileSidebarFillColorChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString profile_text_color READ profileTextColor WRITE setProfileTextColor NOTIFY profileTextColorChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString profile_use_background_image READ profileUseBackgroundImage WRITE setProfileUseBackgroundImage NOTIFY profileUseBackgroundImageChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool protected READ isProtected WRITE setProtected NOTIFY protectedChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool show_all_inline_media READ showAllInlineMedia WRITE setShowAllInlineMedia NOTIFY showAllInlineMediaChanged DESIGNABLE false USER true)
    Q_PROPERTY(int statuses_count READ statusesCount WRITE setStatusesCount NOTIFY statusesCountChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString time_zone READ timeZone WRITE setTimeZone NOTIFY timeZoneChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged DESIGNABLE false USER true)
    Q_PROPERTY(int utc_offset READ utcOffset WRITE setUtcOffset NOTIFY utcOffsetChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool verified READ verified WRITE setVerified NOTIFY verifiedChanged DESIGNABLE false USER true)

    Q_DISABLE_COPY(VerifyCredentials)
public:
    explicit VerifyCredentials(QObject *parent = 0);

    static QVariantMap parse(const QVariantMap &status);

    bool contributorsEnabled() const;
    const QString &createdAt() const;
    const QString &description() const;
    int favouritesCount() const;
    bool followRequestSent() const;
    int followersCount() const;
    bool following() const;
    int friendsCount() const;
    bool geoEnabled() const;
    const QString &idStr() const;
    bool isTranslator() const;
    const QString &lang() const;
    int listedCount() const;
    const QString &location() const;
    const QString &name() const;
    bool notifications() const;
    const QString &profileBackgroundColor() const;
    const QString &profileBackgroundImageUrl() const;
    const QString &profileBackgroundImageUrlHttps() const;
    bool profileBackgroundTile() const;
    const QString &profileImageUrl() const;
    const QString &profileLinkUrl() const;
    const QString &profileSidebarBorderColor() const;
    const QString &profileSidebarFillColor() const;
    const QString &profileTextColor() const;
    const QString &profileUseBackgroundImage() const;
    bool isProtected() const;
    const QString &screenName() const;
    bool showAllInlineMedia() const;
    int statusesCount() const;
    const QString &timeZone() const;
    const QString &url() const;
    int utcOffset() const;
    bool verified() const;

    QVariantMap data() const;

public slots:
    void setContributorsEnabled(bool contributorsEnabled);
    void setCreatedAt(const QString &createdAt);
    void setDescription(const QString &description);
    void setFavouritesCount(int favouritesCount);
    void setFollowRequestSent(bool followRequestSent);
    void setFollowersCount(int followersCount);
    void setFollowing(bool following);
    void setFriendsCount(int friendsCount);
    void setGeoEnabled(bool geoEnabled);
    void setIdStr(const QString &idStr);
    void setIsTranslator(bool isTranslator);
    void setLang(const QString &lang);
    void setListedCount(int listedCount);
    void setLocation(const QString &location);
    void setName(const QString &name);
    void setNotifications(bool notifications);
    void setProfileBackgroundColor(const QString &profileBackgroundColor);
    void setProfileBackgroundImageUrl(const QString &profileBackgroundImageUrl);
    void setProfileBackgroundImageUrlHttps(const QString &profileBackgroundImageUrlHttps);
    void setProfileBackgroundTile(bool profileBackgroundTile);
    void setProfileImageUrl(const QString &profileImageUrl);
    void setProfileLinkUrl(const QString &profileLinkUrl);
    void setProfileSidebarBorderColor(const QString &profileSidebarBorderColor);
    void setProfileSidebarFillColor(const QString &profileSidebarFillColor);
    void setProfileTextColor(const QString &profileTextColor);
    void setProfileUseBackgroundImage(const QString &profileUseBackgroundImage);
    void setProtected(bool isProtected);
    void setScreenName(const QString &screenName);
    void setShowAllInlineMedia(bool showAllInlineMedia);
    void setStatusesCount(int statusesCount);
    void setTimeZone(const QString &timeZone);
    void setUrl(const QString &url);
    void setUtcOffset(int utcOffset);
    void setVerified(bool verified);

signals:
    void loadingChanged(bool loading);
    void contributorsEnabledChanged(bool contributorsEnabled);
    void createdAtChanged(const QString &createdAt);
    void descriptionChanged(const QString &description);
    void favouritesCountChanged(int favouritesCount);
    void followRequestSentChanged(bool followRequestSent);
    void followersCountChanged(int followersCount);
    void followingChanged(bool following);
    void friendsCountChanged(int friendsCount);
    void geoEnabledChanged(bool geoEnabled);
    void idStrChanged(const QString &idStr);
    void isTranslatorChanged(bool isTranslator);
    void langChanged(const QString &lang);
    void listedCountChanged(int listedCount);
    void locationChanged(const QString &location);
    void nameChanged(const QString &name);
    void notificationsChanged(bool notifications);
    void profileBackgroundColorChanged(const QString &profileBackgroundColor);
    void profileBackgroundImageUrlChanged(const QString &profileBackgroundImageUrl);
    void profileBackgroundImageUrlHttpsChanged(const QString &profileBackgroundImageUrlHttps);
    void profileBackgroundTileChanged(bool profileBackgroundTile);
    void profileImageUrlChanged(const QString &profileImageUrl);
    void profileLinkUrlChanged(const QString &profileLinkUrl);
    void profileSidebarBorderColorChanged(const QString &profileSidebarBorderColor);
    void profileSidebarFillColorChanged(const QString &profileSidebarFillColor);
    void profileTextColorChanged(const QString &profileTextColor);
    void profileUseBackgroundImageChanged(const QString &profileUseBackgroundImage);
    void protectedChanged(bool isProtected);
    void screenNameChanged(const QString &screenName);
    void showAllInlineMediaChanged(bool showAllInlineMedia);
    void statusesCountChanged(int statusesCount);
    void timeZoneChanged(const QString &timeZone);
    void urlChanged(const QString &url);
    void utcOffsetChanged(int utcOffset);
    void verifiedChanged(bool verified);

    void dataChanged();

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/account/verify_credentials.json"); }
    QString httpMethod() const { return "GET"; }

private:
    class Private;
    Private *d;
};

#endif // VERIFYCREDENTIALS_H
