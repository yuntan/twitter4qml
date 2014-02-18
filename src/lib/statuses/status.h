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

#ifndef STATUS_H
#define STATUS_H

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

// Tweet specification  https://dev.twitter.com/docs/platform-objects/tweets
class TWITTER4QML_EXPORT Status : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(PostStatus postStatus READ postStatus NOTIFY postStatusChanged DESIGNABLE false)
    Q_PROPERTY(QVariantList contributors READ contributors WRITE contributors NOTIFY contributorsChanged)
    Q_PROPERTY(QVariantMap coordinates READ coordinates WRITE coordinates NOTIFY coordinatesChanged)
    Q_PROPERTY(QString created_at READ created_at WRITE created_at NOTIFY created_atChanged)
    Q_PROPERTY(QVariantList current_user_retweet READ current_user_retweet WRITE current_user_retweet NOTIFY current_user_retweetChanged)
    Q_PROPERTY(QVariantMap entities READ entities WRITE entities NOTIFY entitiesChanged)
    Q_PROPERTY(int favorite_count READ favorite_count WRITE favorite_count NOTIFY favorite_countChanged)
    Q_PROPERTY(bool favorited READ favorited WRITE favorited NOTIFY favoritedChanged)
    Q_PROPERTY(QString filter_level READ filter_level WRITE filter_level NOTIFY filter_levelChanged)
    Q_PROPERTY(QVariantMap geo READ geo WRITE geo NOTIFY geoChanged)
    Q_PROPERTY(long long id READ id WRITE id NOTIFY idChanged)
    Q_PROPERTY(QString id_str READ id_str WRITE id_str NOTIFY id_strChanged)
    Q_PROPERTY(QString in_reply_to_screen_name READ in_reply_to_screen_name WRITE in_reply_to_screen_name NOTIFY in_reply_to_screen_nameChanged)
    Q_PROPERTY(long long in_reply_to_status_id READ in_reply_to_status_id WRITE in_reply_to_status_id NOTIFY in_reply_to_status_idChanged)
    Q_PROPERTY(QString in_reply_to_status_id_str READ in_reply_to_status_id_str WRITE in_reply_to_status_id_str NOTIFY in_reply_to_status_id_strChanged)
    Q_PROPERTY(long long in_reply_to_user_id READ in_reply_to_user_id WRITE in_reply_to_user_id NOTIFY in_reply_to_user_idChanged)
    Q_PROPERTY(QString in_reply_to_user_id_str READ in_reply_to_user_id_str WRITE in_reply_to_user_id_str NOTIFY in_reply_to_user_id_strChanged)
    Q_PROPERTY(QString lang READ lang WRITE lang NOTIFY langChanged)
    Q_PROPERTY(QVariantMap place READ place WRITE place NOTIFY placeChanged)
    Q_PROPERTY(bool possibly_sensitive READ possibly_sensitive WRITE possibly_sensitive NOTIFY possibly_sensitiveChanged)
    Q_PROPERTY(QVariantList scopes READ scopes WRITE scopes NOTIFY scopesChanged)
    Q_PROPERTY(int retweet_count READ retweet_count WRITE retweet_count NOTIFY retweet_countChanged)
    Q_PROPERTY(bool retweeted READ retweeted WRITE retweeted NOTIFY retweetedChanged)
    Q_PROPERTY(QVariantMap retweeted_status READ retweeted_status WRITE retweeted_status NOTIFY retweeted_statusChanged)
    Q_PROPERTY(QString source READ source WRITE source NOTIFY sourceChanged)
    Q_PROPERTY(QString text READ text WRITE text NOTIFY textChanged)
    Q_PROPERTY(QString plain_text READ plain_text WRITE plain_text NOTIFY plain_textChanged)
    Q_PROPERTY(QString rich_text READ rich_text WRITE rich_text NOTIFY rich_textChanged)
    Q_PROPERTY(bool truncated READ truncated WRITE truncated NOTIFY truncatedChanged)
    Q_PROPERTY(QVariantMap user READ user WRITE user NOTIFY userChanged)
    Q_PROPERTY(bool withheld_copyright READ withheld_copyright WRITE withheld_copyright NOTIFY withheld_copyrightChanged)
    Q_PROPERTY(QVariantMap withheld_in_countries READ withheld_in_countries WRITE withheld_in_countries NOTIFY withheld_in_countriesChanged)
    Q_PROPERTY(QString withheld_scope READ withheld_scope WRITE withheld_scope NOTIFY withheld_scopeChanged)
    Q_PROPERTY(QVariantList media READ media WRITE media NOTIFY mediaChanged)
    Q_PROPERTY(QVariantMap data READ data NOTIFY dataChanged DESIGNABLE false)
    Q_DISABLE_COPY(Status)
public:
    explicit Status(QObject *parent = 0);

    enum PostStatus {
        Success = Qt::UserRole,
        RateLimitExceeded, // code 88
        OverCapacity, // code 130
        InternalError, // code 131
        TimeInvalid, // code 135
        Duplicate, // code 187
        Unknown
    };
    Q_ENUMS(PostStatus)

    static QVariantMap parse(const QVariantMap &status);
    static bool indicesGreaterThan(const QVariant &v1, const QVariant &v2);

    QVariantMap data() const;

    Q_INVOKABLE void statusesUpdate(QVariantMap parameters);
    Q_INVOKABLE void statusesRetweet(QVariantMap parameters);
    Q_INVOKABLE void statusesDestroy();
    Q_INVOKABLE void favorite();
    Q_INVOKABLE void unfavorite();

    Q_INVOKABLE void debug() const;

public slots:

signals:
    void loadingChanged(bool loading);
    void postStatusChanged(PostStatus postStatus);
    void contributorsChanged(const QVariantList &contributors) const;
    void coordinatesChanged(const QVariantMap &coordinates);
    void created_atChanged(const QString &created_at);
    void current_user_retweetChanged(const QVariantList &current_user_retweet);
    void entitiesChanged(const QVariantMap &entities);
    void favorite_countChanged(int favorite_count);
    void favoritedChanged(bool favorited);
    void filter_levelChanged(const QString &filter_level);
    void geoChanged(const QVariantMap &geo);
    void idChanged(long long id);
    void id_strChanged(const QString &id_str);
    void in_reply_to_screen_nameChanged(const QString &in_reply_to_screen_name);
    void in_reply_to_status_idChanged(long long in_reply_to_status_id);
    void in_reply_to_status_id_strChanged(const QString &in_reply_to_status_id_str);
    void in_reply_to_user_idChanged(long long in_reply_to_user_id);
    void in_reply_to_user_id_strChanged(const QString &in_reply_to_user_id_str);
    void langChanged(const QString &lang);
    void placeChanged(const QVariantMap &place);
    void possibly_sensitiveChanged(bool possibly_sensitive);
    void scopesChanged(const QVariantList &scopes);
    void retweet_countChanged(int retweet_count);
    void retweetedChanged(bool retweeted);
    void retweeted_statusChanged(const QVariantMap &retweeted_status);
    void sourceChanged(const QString &source);
    void textChanged(const QString &text);
    void plain_textChanged(const QString &plain_text);
    void rich_textChanged(const QString &rich_text);
    void truncatedChanged(bool truncated);
    void userChanged(const QVariantMap &user);
    void withheld_copyrightChanged(bool withheld_copyright);
    void withheld_in_countriesChanged(const QVariantMap &withheld_in_countries);
    void withheld_scopeChanged(const QString &withheld_scope);
    void mediaChanged(const QVariantList &media) const;
    void dataChanged();

private:
    class Private;
    Private *d;

    ADD_PROPERTY(bool, loading, bool)
    ADD_PROPERTY(PostStatus, postStatus, PostStatus)
    ADD_PROPERTY(const QVariantList &, contributors, QVariantList)
    ADD_PROPERTY(const QVariantMap &, coordinates, QVariantMap)
    ADD_PROPERTY(const QString &, created_at, QString)
    ADD_PROPERTY(const QVariantList &, current_user_retweet, QVariantList)
    ADD_PROPERTY(const QVariantMap &, entities, QVariantMap)
    ADD_PROPERTY(int, favorite_count, int)
    ADD_PROPERTY(bool, favorited, bool)
    ADD_PROPERTY(const QString &, filter_level, QString)
    ADD_PROPERTY(const QVariantMap &, geo, QVariantMap)
    ADD_PROPERTY(long long, id, long long)
    ADD_PROPERTY(const QString &, id_str, QString)
    ADD_PROPERTY(const QString &, in_reply_to_screen_name, QString)
    ADD_PROPERTY(long long, in_reply_to_status_id, long long)
    ADD_PROPERTY(const QString &, in_reply_to_status_id_str, QString)
    ADD_PROPERTY(long long, in_reply_to_user_id, long long)
    ADD_PROPERTY(const QString &, in_reply_to_user_id_str, QString)
    ADD_PROPERTY(const QString &, lang, QString)
    ADD_PROPERTY(const QVariantMap &, place, QVariantMap)
    ADD_PROPERTY(bool, possibly_sensitive, bool)
    ADD_PROPERTY(const QVariantList &, scopes, QVariantList)
    ADD_PROPERTY(int, retweet_count, int)
    ADD_PROPERTY(bool, retweeted, bool)
    ADD_PROPERTY(const QVariantMap &, retweeted_status, QVariantMap)
    ADD_PROPERTY(const QString &, source, QString)
    ADD_PROPERTY(const QString &, text, QString)
    ADD_PROPERTY(const QString &, plain_text, QString)
    ADD_PROPERTY(const QString &, rich_text, QString)
    ADD_PROPERTY(bool, truncated, bool)
    ADD_PROPERTY(const QVariantMap &, user, QVariantMap)
    ADD_PROPERTY(bool, withheld_copyright, bool)
    ADD_PROPERTY(const QVariantMap &, withheld_in_countries, QVariantMap)
    ADD_PROPERTY(const QString &, withheld_scope, QString)
    ADD_PROPERTY(const QVariantList &, media, QVariantList)
};

#endif // STATUS_H
