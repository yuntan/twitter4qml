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

#ifndef SETTINGS_H
#define SETTINGS_H

#include "../tools/abstracttwitteraction.h"

class Settings : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(Settings)
    Q_PROPERTY(bool always_use_https READ always_use_https WRITE always_use_https NOTIFY always_use_httpsChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool discoverable_by_email READ discoverable_by_email WRITE discoverable_by_email NOTIFY discoverable_by_emailChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool geo_enabled READ geo_enabled WRITE geo_enabled NOTIFY geo_enabledChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString language READ language WRITE language NOTIFY languageChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool _protected READ _protected WRITE _protected NOTIFY _protectedChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString screen_name READ screen_name WRITE screen_name NOTIFY screen_nameChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool show_all_inline_media READ show_all_inline_media WRITE show_all_inline_media NOTIFY show_all_inline_mediaChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantMap sleep_time READ sleep_time WRITE sleep_time NOTIFY sleep_timeChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantMap time_zone READ time_zone WRITE time_zone NOTIFY time_zoneChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantList trend_location READ trend_location WRITE trend_location NOTIFY trend_locationChanged DESIGNABLE false USER true)

public:
    explicit Settings(QObject *parent = 0);

signals:
    void always_use_httpsChanged(bool always_use_https);
    void discoverable_by_emailChanged(bool discoverable_by_email);
    void geo_enabledChanged(bool geo_enabled);
    void languageChanged(const QString &language);
    void _protectedChanged(bool _protected);
    void screen_nameChanged(const QString &screen_name);
    void show_all_inline_mediaChanged(bool show_all_inline_media);
    void sleep_timeChanged(const QVariantMap &sleep_time);
    void trend_locationChanged(const QVariantList &trend_location);
    void time_zoneChanged(const QVariantMap &time_zone);

protected:
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/account/settings.json"); }
    QString httpMethod() const { return "GET"; }

private:
    ADD_PROPERTY(bool, always_use_https, bool)
    ADD_PROPERTY(bool, discoverable_by_email, bool)
    ADD_PROPERTY(bool, geo_enabled, bool)
    ADD_PROPERTY(const QString &, language, QString)
    ADD_PROPERTY(bool, _protected, bool)
    ADD_PROPERTY(const QString &, screen_name, QString)
    ADD_PROPERTY(bool, show_all_inline_media, bool)
    ADD_PROPERTY(const QVariantMap &, sleep_time, QVariantMap)
    ADD_PROPERTY(const QVariantMap &, time_zone, QVariantMap)
    ADD_PROPERTY(const QVariantList &, trend_location, QVariantList)
};

#endif // SETTINGS_H
