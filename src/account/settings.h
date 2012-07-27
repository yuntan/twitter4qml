#ifndef SETTINGS_H
#define SETTINGS_H

#include "../tools/abstracttwitteraction.h"

class Settings : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(Settings)
    Q_PROPERTY(bool always_use_https READ alwaysUseHttps WRITE setAlwaysUseHttps NOTIFY alwaysUseHttpsChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool discoverable_by_email READ discoverableByEmail WRITE setDiscoverableByEmail NOTIFY discoverableByEmailChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool geo_enabled READ geoEnabled WRITE setGeoEnabled NOTIFY geoEnabledChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool _protected READ isProtected WRITE setProtected NOTIFY protectedChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool show_all_inline_media READ showAllInlineMedia WRITE setShowAllInlineMedia NOTIFY showAllInlineMediaChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantMap sleep_time READ sleepTime WRITE setSleepTime NOTIFY sleepTimeChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantMap time_zone READ timeZone WRITE setTimeZone NOTIFY timeZoneChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantList trend_location READ trendLocation WRITE setTrendLocation NOTIFY trendLocationChanged DESIGNABLE false USER true)

public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

    bool alwaysUseHttps() const;
    void setAlwaysUseHttps(bool alwaysUseHttps);
    bool discoverableByEmail() const;
    void setDiscoverableByEmail(bool discoverableByEmail);
    bool geoEnabled() const;
    void setGeoEnabled(bool geoEnabled);
    const QString &language() const;
    void setLanguage(const QString &language);
    bool isProtected() const;
    void setProtected(bool isProtected);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    bool showAllInlineMedia() const;
    void setShowAllInlineMedia(bool showAllInlineMedia);
    const QVariantMap &sleepTime() const;
    void setSleepTime(const QVariantMap &sleepTime);
    const QVariantMap &timeZone() const;
    void setTimeZone(const QVariantMap &timeZone);
    const QVariantList &trendLocation() const;
    void setTrendLocation(const QVariantList &trendLocation);

signals:
    void alwaysUseHttpsChanged(bool alwaysUseHttps);
    void discoverableByEmailChanged(bool discoverableByEmail);
    void geoEnabledChanged(bool geoEnabled);
    void languageChanged(const QString &language);
    void protectedChanged(bool isProtected);
    void screenNameChanged(const QString &screenName);
    void showAllInlineMediaChanged(bool showAllInlineMedia);
    void sleepTimeChanged(const QVariantMap &sleepTime);
    void trendLocationChanged(const QVariantList &trendLocation);
    void timeZoneChanged(const QVariantMap &timeZone);

protected:
    QUrl api() const { return QUrl("https://api.twitter.com/1/account/settings.json"); }
    QString httpMethod() const { return "GET"; }

private:
    class Private;
    Private *d;
};

#endif // SETTINGS_H
