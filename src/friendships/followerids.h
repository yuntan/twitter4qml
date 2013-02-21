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

#ifndef FOLLOWERIDS_H
#define FOLLOWERIDS_H

#include "abstractfriendshipidsmodel.h"

class FollowerIds : public AbstractFriendshipIdsModel
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ user_id WRITE user_id NOTIFY user_idChanged)
    Q_PROPERTY(QString screen_name READ screen_name WRITE screen_name NOTIFY screen_nameChanged)
    Q_PROPERTY(QString cursor READ cursor WRITE cursor NOTIFY cursorChanged)
    Q_PROPERTY(bool stringify_ids READ stringify_ids WRITE stringify_ids NOTIFY stringify_idsChanged)
    Q_PROPERTY(int count READ count WRITE count NOTIFY countChanged)
public:
    explicit FollowerIds(QObject *parent = 0);

signals:
    void user_idChanged(const QString &user_id);
    void screen_nameChanged(const QString &screen_name);
    void cursorChanged(const QString &cursor);
    void stringify_idsChanged(bool stringify_ids);
    void countChanged(int count);

protected:
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/followers/ids.json"); }
};

#endif // FOLLOWERIDS_H