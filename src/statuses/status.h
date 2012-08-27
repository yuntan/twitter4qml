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

#ifndef STATUS_H
#define STATUS_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "twitter4qml_global.h"

class Status : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(QVariantList contributors READ contributors WRITE setContributors NOTIFY contributorsChanged)
    Q_PROPERTY(QVariantMap coordinates READ coordinates WRITE setCoordinates NOTIFY coordinatesChanged)
    Q_PROPERTY(QString created_at READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QVariantMap entities READ entities WRITE setEntities NOTIFY entitiesChanged)
    Q_PROPERTY(bool favorited READ favorited WRITE setFavorited NOTIFY favoritedChanged)
    Q_PROPERTY(QVariantMap geo READ geo WRITE setGeo NOTIFY geoChanged)
    Q_PROPERTY(QString id_str READ idStr WRITE setIdStr NOTIFY idStrChanged)
    Q_PROPERTY(QString in_reply_to_screen_name READ inReplyToScreenName WRITE setInReplyToScreenName NOTIFY inReplyToScreenNameChanged)
    Q_PROPERTY(QString in_reply_to_status_id_str READ inReplyToStatusIdStr WRITE setInReplyToStatusIdStr NOTIFY inReplyToStatusIdStrChanged)
    Q_PROPERTY(QString in_reply_to_user_id_str READ inReplyToUserIdStr WRITE setInReplyToUserIdStr NOTIFY inReplyToUserIdStrChanged)
    Q_PROPERTY(QVariantMap place READ place WRITE setPlace NOTIFY placeChanged)
    Q_PROPERTY(bool possibly_sensitive READ possiblySensitive WRITE setPossiblySensitive NOTIFY possiblySensitiveChanged)
    Q_PROPERTY(int retweet_count READ retweetCount WRITE setRetweetCount NOTIFY retweetCountChanged)
    Q_PROPERTY(bool retweeted READ retweeted WRITE setRetweeted NOTIFY retweetedChanged)
    Q_PROPERTY(QVariantMap retweeted_status READ retweetedStatus WRITE setRetweetedStatus NOTIFY retweetedStatusChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString plain_text READ plainText WRITE setPlainText NOTIFY plainTextChanged)
    Q_PROPERTY(QString rich_text READ richText WRITE setRichText NOTIFY richTextChanged)
    Q_PROPERTY(bool truncated READ truncated WRITE setTruncated NOTIFY truncatedChanged)
    Q_PROPERTY(QVariantMap user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(QVariantList media READ media WRITE setMedia NOTIFY mediaChanged)
    Q_PROPERTY(QVariantMap data READ data NOTIFY dataChanged DESIGNABLE false)
    Q_DISABLE_COPY(Status)
public:
    explicit Status(QObject *parent = 0);

    static QVariantMap parse(const QVariantMap &status);
    static bool indicesGreaterThan(const QVariant &v1, const QVariant &v2);

    bool loading() const;
    const QVariantList &contributors() const;
    const QVariantMap &coordinates() const;
    const QString &createdAt() const;
    const QVariantMap &entities() const;
    bool favorited() const;
    const QVariantMap &geo() const;
    const QString &idStr() const;
    const QString &inReplyToScreenName() const;
    const QString &inReplyToStatusIdStr() const;
    const QString &inReplyToUserIdStr() const;
    const QVariantMap &place() const;
    bool possiblySensitive() const;
    int retweetCount() const;
    bool retweeted() const;
    const QVariantMap &retweetedStatus() const;
    const QString &source() const;
    const QString &text() const;
    const QString &plainText() const;
    const QString &richText() const;
    bool truncated() const;
    const QVariantMap &user() const;
    const QVariantList &media() const;
    QVariantMap data() const;

    Q_INVOKABLE void updateStatus(QVariantMap parameters);
    Q_INVOKABLE void retweetStatus(QVariantMap parameters);
    Q_INVOKABLE void destroyStatus();
    Q_INVOKABLE void favorite();
    Q_INVOKABLE void unfavorite();

    Q_INVOKABLE void debug() const;

public slots:
    void setContributors(const QVariantList &contributors);
    void setCoordinates(const QVariantMap &coordinates);
    void setCreatedAt(const QString &createdAt);
    void setEntities(const QVariantMap &entities);
    void setFavorited(bool favorited);
    void setGeo(const QVariantMap &geo);
    void setIdStr(const QString &idStr);
    void setInReplyToScreenName(const QString &inReplyToScreenName);
    void setInReplyToStatusIdStr(const QString &inReplyToStatusIdStr);
    void setInReplyToUserIdStr(const QString &inReplyToUserIdStr);
    void setPlace(const QVariantMap &place);
    void setPossiblySensitive(bool possiblySensitive);
    void setRetweetCount(int retweetCount);
    void setRetweeted(bool retweeted);
    void setRetweetedStatus(const QVariantMap &retweetedStatus);
    void setSource(const QString &source);
    void setText(const QString &text);
    void setPlainText(const QString &plainText);
    void setRichText(const QString &richText);
    void setTruncated(bool truncated);
    void setUser(const QVariantMap &user);
    void setMedia(const QVariantList &media);

signals:
    void loadingChanged(bool loading);
    void contributorsChanged(const QVariantList &contributors) const;
    void coordinatesChanged(const QVariantMap &coordinates);
    void createdAtChanged(const QString &createdAt);
    void entitiesChanged(const QVariantMap &entities);
    void favoritedChanged(bool favorited);
    void geoChanged(const QVariantMap &geo);
    void idStrChanged(const QString &idStr);
    void inReplyToScreenNameChanged(const QString &inReplyToScreenName);
    void inReplyToStatusIdStrChanged(const QString &inReplyToStatusIdStr);
    void inReplyToUserIdStrChanged(const QString &inReplyToUserIdStr);
    void placeChanged(const QVariantMap &place);
    void possiblySensitiveChanged(bool possiblySensitive);
    void retweetCountChanged(int retweetCount);
    void retweetedChanged(bool retweeted);
    void retweetedStatusChanged(const QVariantMap &retweetedStatus);
    void sourceChanged(const QString &source);
    void textChanged(const QString &text);
    void plainTextChanged(const QString &plainText);
    void richTextChanged(const QString &richText);
    void truncatedChanged(bool truncated);
    void userChanged(const QVariantMap &user);
    void mediaChanged(const QVariantList &media) const;
    void dataChanged();

private:
    class Private;
    Private *d;
};

#endif // STATUS_H
