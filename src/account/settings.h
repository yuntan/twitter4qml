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
