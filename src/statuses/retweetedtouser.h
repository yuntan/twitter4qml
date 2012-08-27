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

#ifndef RETWEETEDTOUSER_H
#define RETWEETEDTOUSER_H

#include "abstractstatusesmodel.h"

class RetweetedToUser : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool trim_user READ trimUser WRITE setTrimUser NOTIFY trimUserChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(RetweetedToUser)
public:
    explicit RetweetedToUser(QObject *parent = 0);

signals:
    void screenNameChanged(const QString &screenName);
    void idChanged(const QString &id);
    void countChanged(int count);
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void pageChanged(int page);
    void trimUserChanged(bool trimUser);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/statuses/retweeted_to_user.json"); }
};

#endif // RETWEETEDTOUSER_H
