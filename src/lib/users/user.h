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

#ifndef USER_H
#define USER_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "twitter4qml_global.h"

#define ADD_PROPERTY(type, name, type2) \
public: \
    type name() const { return m_##name; } \
    void name(type name) { \
        if (m_##name == name) return; \
        m_##name = name; \
        emit name##Changed(name); \
    } \
private: \
    type2 m_##name;

class TWITTER4QML_EXPORT User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(bool contributors_enabled READ contributors_enabled WRITE contributors_enabled NOTIFY contributors_enabledChanged)
    Q_PROPERTY(QString created_at READ created_at WRITE created_at NOTIFY created_atChanged)
    //    Q_PROPERTY(QString default_profile READ defaultProfile WRITE setDefaultProfile NOTIFY defaultProfileChanged)
    //    Q_PROPERTY(QString default_profile_image READ defaultProfileImage WRITE setDefaultProfileImage NOTIFY defaultProfileImageChanged)
    Q_PROPERTY(QString description READ description WRITE description NOTIFY descriptionChanged)
    Q_PROPERTY(int favourites_count READ favourites_count WRITE favourites_count NOTIFY favourites_countChanged)
    Q_PROPERTY(bool follow_request_sent READ follow_request_sent WRITE follow_request_sent NOTIFY follow_request_sentChanged)
    Q_PROPERTY(int followers_count READ followers_count WRITE followers_count NOTIFY followers_countChanged)
    Q_PROPERTY(bool following READ following WRITE following NOTIFY followingChanged)
    Q_PROPERTY(int friends_count READ friends_count WRITE friends_count NOTIFY friends_countChanged)
    Q_PROPERTY(bool geo_enabled READ geo_enabled WRITE geo_enabled NOTIFY geo_enabledChanged)
    Q_PROPERTY(QString id_str READ id_str WRITE id_str NOTIFY id_strChanged)
    Q_PROPERTY(bool is_translator READ is_translator WRITE is_translator NOTIFY is_translatorChanged)
    Q_PROPERTY(QString lang READ lang WRITE lang NOTIFY langChanged)
    Q_PROPERTY(int listed_count READ listed_count WRITE listed_count NOTIFY listed_countChanged)
    Q_PROPERTY(QString location READ location WRITE location NOTIFY locationChanged)
    Q_PROPERTY(QString name READ name WRITE name NOTIFY nameChanged)
    Q_PROPERTY(bool notifications READ notifications WRITE notifications NOTIFY notificationsChanged)
    Q_PROPERTY(QString profile_background_color READ profile_background_color WRITE profile_background_color NOTIFY profile_background_colorChanged)
    Q_PROPERTY(QString profile_background_image_url READ profile_background_image_url WRITE profile_background_image_url NOTIFY profile_background_image_urlChanged)
    Q_PROPERTY(QString profile_background_image_url_https READ profile_background_image_url_https WRITE profile_background_image_url_https NOTIFY profile_background_image_url_httpsChanged)
    Q_PROPERTY(bool profile_background_tile READ profile_background_tile WRITE profile_background_tile NOTIFY profile_background_tileChanged)
    Q_PROPERTY(QString profile_image_url READ profile_image_url WRITE profile_image_url NOTIFY profile_image_urlChanged)
    Q_PROPERTY(QString profile_link_url READ profile_link_url WRITE profile_link_url NOTIFY profile_link_urlChanged)
    Q_PROPERTY(QString profile_sidebar_border_color READ profile_sidebar_border_color WRITE profile_sidebar_border_color NOTIFY profile_sidebar_border_colorChanged)
    Q_PROPERTY(QString profile_sidebar_fill_color READ profile_sidebar_fill_color WRITE profile_sidebar_fill_color NOTIFY profile_sidebar_fill_colorChanged)
    Q_PROPERTY(QString profile_text_color READ profile_text_color WRITE profile_text_color NOTIFY profile_text_colorChanged)
    Q_PROPERTY(QString profile_use_background_image READ profile_use_background_image WRITE profile_use_background_image NOTIFY profile_use_background_imageChanged)
    Q_PROPERTY(bool protected READ _protected WRITE _protected NOTIFY _protectedChanged)
    Q_PROPERTY(QString screen_name READ screen_name WRITE screen_name NOTIFY screen_nameChanged)
    Q_PROPERTY(bool show_all_inline_media READ show_all_inline_media WRITE show_all_inline_media NOTIFY show_all_inline_mediaChanged)
    Q_PROPERTY(int statuses_count READ statuses_count WRITE statuses_count NOTIFY statuses_countChanged)
    Q_PROPERTY(QString time_zone READ time_zone WRITE time_zone NOTIFY time_zoneChanged)
    Q_PROPERTY(QString url READ url WRITE url NOTIFY urlChanged)
    Q_PROPERTY(int utc_offset READ utc_offset WRITE utc_offset NOTIFY utc_offsetChanged)
    Q_PROPERTY(bool verified READ verified WRITE verified NOTIFY verifiedChanged)
    Q_PROPERTY(bool blocking READ blocking WRITE blocking NOTIFY blockingChanged)

    Q_DISABLE_COPY(User)
public:
    explicit User(QObject *parent = 0);

    static QVariantMap parse(const QVariantMap &status);

    bool loading() const;

    QVariantMap data() const;

    Q_INVOKABLE void follow();
    Q_INVOKABLE void unfollow();
    Q_INVOKABLE void block();
    Q_INVOKABLE void unblock();
    Q_INVOKABLE void reportForSpam();

    Q_INVOKABLE void debug() const;

signals:
    void loadingChanged(bool loading);
    void contributors_enabledChanged(bool contributors_enabled);
    void created_atChanged(const QString &created_at);
    void descriptionChanged(const QString &description);
    void favourites_countChanged(int favourites_count);
    void follow_request_sentChanged(bool follow_request_sent);
    void followers_countChanged(int followers_count);
    void followingChanged(bool following);
    void friends_countChanged(int friends_count);
    void geo_enabledChanged(bool geo_enabled);
    void id_strChanged(const QString &id_str);
    void is_translatorChanged(bool is_translator);
    void langChanged(const QString &lang);
    void listed_countChanged(int listed_count);
    void locationChanged(const QString &location);
    void nameChanged(const QString &name);
    void notificationsChanged(bool notifications);
    void profile_background_colorChanged(const QString &profile_background_color);
    void profile_background_image_urlChanged(const QString &profile_background_image_url);
    void profile_background_image_url_httpsChanged(const QString &profile_background_image_url_https);
    void profile_background_tileChanged(bool profile_background_tile);
    void profile_image_urlChanged(const QString &profile_image_url);
    void profile_link_urlChanged(const QString &profile_link_url);
    void profile_sidebar_border_colorChanged(const QString &profile_sidebar_border_color);
    void profile_sidebar_fill_colorChanged(const QString &profile_sidebar_fill_color);
    void profile_text_colorChanged(const QString &profile_text_color);
    void profile_use_background_imageChanged(const QString &profile_use_background_image);
    void _protectedChanged(bool _protected);
    void screen_nameChanged(const QString &screen_name);
    void show_all_inline_mediaChanged(bool show_all_inline_media);
    void statuses_countChanged(int statuses_count);
    void time_zoneChanged(const QString &time_zone);
    void urlChanged(const QString &url);
    void utc_offsetChanged(int utc_offset);
    void verifiedChanged(bool verified);
    void blockingChanged(bool blocking);

    void dataChanged();

private:
    class Private;
    Private *d;

    ADD_PROPERTY(bool, contributors_enabled, bool)
    ADD_PROPERTY(const QString &, created_at, QString)
    ADD_PROPERTY(const QString &, description, QString)
    ADD_PROPERTY(int, favourites_count, int)
    ADD_PROPERTY(bool, follow_request_sent, bool)
    ADD_PROPERTY(int, followers_count, int)
    ADD_PROPERTY(bool, following, bool)
    ADD_PROPERTY(int, friends_count, int)
    ADD_PROPERTY(bool, geo_enabled, bool)
    ADD_PROPERTY(const QString &, id_str, QString)
    ADD_PROPERTY(bool, is_translator, bool)
    ADD_PROPERTY(const QString &, lang, QString)
    ADD_PROPERTY(int, listed_count, int)
    ADD_PROPERTY(const QString &, location, QString)
    ADD_PROPERTY(const QString &, name, QString)
    ADD_PROPERTY(bool, notifications, bool)
    ADD_PROPERTY(const QString &, profile_background_color, QString)
    ADD_PROPERTY(const QString &, profile_background_image_url, QString)
    ADD_PROPERTY(const QString &, profile_background_image_url_https, QString)
    ADD_PROPERTY(bool, profile_background_tile, bool)
    ADD_PROPERTY(const QString &, profile_image_url, QString)
    ADD_PROPERTY(const QString &, profile_link_url, QString)
    ADD_PROPERTY(const QString &, profile_sidebar_border_color, QString)
    ADD_PROPERTY(const QString &, profile_sidebar_fill_color, QString)
    ADD_PROPERTY(const QString &, profile_text_color, QString)
    ADD_PROPERTY(const QString &, profile_use_background_image, QString)
    ADD_PROPERTY(bool, _protected, bool)
    ADD_PROPERTY(const QString &, screen_name, QString)
    ADD_PROPERTY(bool, show_all_inline_media, bool)
    ADD_PROPERTY(int, statuses_count, int)
    ADD_PROPERTY(const QString &, time_zone, QString)
    ADD_PROPERTY(const QString &, url, QString)
    ADD_PROPERTY(int, utc_offset, int)
    ADD_PROPERTY(bool, verified, bool)
    ADD_PROPERTY(bool, blocking, bool)
};

#endif // USER_H
