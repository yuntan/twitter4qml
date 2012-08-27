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

#ifndef USERTIMELINE_H
#define USERTIMELINE_H

#include "abstractstatusesmodel.h"

class UserTimeline : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool trim_user READ trimUser WRITE setTrimUser NOTIFY trimUserChanged)
    Q_PROPERTY(bool include_rts READ includeRts WRITE setIncludeRts NOTIFY includeRtsChanged)
    Q_PROPERTY(bool exclude_replies READ excludeReplies WRITE setExcludeReplies NOTIFY excludeRepliesChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_PROPERTY(bool contributor_details READ contributorDetails WRITE setContributorDetails NOTIFY contributorDetailsChanged)
    Q_DISABLE_COPY(UserTimeline)
public:
    explicit UserTimeline(QObject *parent = 0);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void sinceIdChanged(const QString &sinceId);
    void countChanged(int count);
    void maxIdChanged(const QString &maxId);
    void pageChanged(int page);
    void trimUserChanged(bool trimUser);
    void includeRtsChanged(bool includeRts);
    void excludeRepliesChanged(bool excludeReplies);
    void includeEntitiesChanged(bool includeEntities);
    void contributorDetailsChanged(bool contributorDetails);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/statuses/user_timeline.json"); }
    void dataAdded(const QString &key, const QVariantMap &value);
};

#endif // USERTIMELINE_H
