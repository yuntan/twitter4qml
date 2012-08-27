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

#ifndef USERSTREAM_H
#define USERSTREAM_H

#include "../statuses/abstractstatusesmodel.h"

class UserStream : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString delimited READ delimited WRITE setDelimited NOTIFY delimitedChanged)
    Q_PROPERTY(QString replies READ replies WRITE setReplies NOTIFY repliesChanged)
    Q_PROPERTY(QStringList friends READ friends NOTIFY friendsChanged DESIGNABLE false)
    Q_DISABLE_COPY(UserStream)
public:
    explicit UserStream(QObject *parent = 0);
    ~UserStream();
    
    const QString &delimited() const;
    const QString &replies() const;
    const QStringList &friends() const;

public slots:
    void setDelimited(const QString &delimited);
    void setReplies(const QString &replies);

signals:
    void delimitedChanged(const QString &delimited);
    void repliesChanged(const QString &replies);
    void friendsChanged(const QStringList &friends);

    void followedBy(const QVariantMap &status);
    void favorited(const QVariantMap &status);
    void unfavorited(const QVariantMap &status);

protected:
    bool isStreaming() const { return true; }
    QUrl api() const { return QUrl("https://userstream.twitter.com/2/user.json"); }
    QString httpMethod() const { return "POST"; }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // USERSTREAM_H
