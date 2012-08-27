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

#ifndef SHOWFRIENDSHIP_H
#define SHOWFRIENDSHIP_H

#include "../tools/abstracttwitteraction.h"

class ShowFriendships : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString source_id READ sourceId WRITE setSourceId NOTIFY sourceIdChanged)
    Q_PROPERTY(QString source_screen_name READ sourceScreenName WRITE setSourceScreenName NOTIFY sourceScreenNameChanged)
    Q_PROPERTY(QString target_id READ targetId WRITE setTargetId NOTIFY targetIdChanged)
    Q_PROPERTY(QString target_screen_name READ targetScreenName WRITE setTargetScreenName NOTIFY targetScreenNameChanged)
    Q_PROPERTY(QVariantMap relationship READ relationship WRITE setRelationship NOTIFY relationshipChanged DESIGNABLE false USER true)
public:
    explicit ShowFriendships(QObject *parent = 0);

    const QString &sourceId() const;
    void setSourceId(const QString &sourceId);
    const QString &sourceScreenName() const;
    void setSourceScreenName(const QString &sourceScreenName);
    const QString &targetId() const;
    void setTargetId(const QString &targetId);
    const QString &targetScreenName() const;
    void setTargetScreenName(const QString &targetScreenName);
    const QVariantMap &relationship() const;
    void setRelationship(const QVariantMap &relationship);

public slots:
    void exec();

signals:
    void sourceIdChanged(const QString &sourceId);
    void sourceScreenNameChanged(const QString &sourceScreenName);
    void targetIdChanged(const QString &targetId);
    void targetScreenNameChanged(const QString &targetScreenName);
    void relationshipChanged(const QVariantMap &relationship);
protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/friendships/show.json"); }
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }

private:
    class Private;
    Private *d;
};

#endif // SHOWFRIENDSHIP_H
