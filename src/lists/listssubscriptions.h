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

#ifndef LISTSSUBSCRIPTIONS_H
#define LISTSSUBSCRIPTIONS_H

#include "abstractlistsmodel.h"

class ListsSubscriptions : public AbstractListsModel
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString cursor READ cursor WRITE setCursor NOTIFY cursorChanged)

    Q_PROPERTY(int next_cursor READ nextCursor NOTIFY nextCursorChanged DESIGNABLE false)
    Q_PROPERTY(QString next_cursor_str READ nextCursorStr NOTIFY nextCursorStrChanged DESIGNABLE false)
    Q_PROPERTY(int previous_cursor READ previousCursor NOTIFY previousCursorChanged DESIGNABLE false)
    Q_PROPERTY(QString previous_cursor_str READ previousCursorStr NOTIFY previousCursorStrChanged DESIGNABLE false)
    Q_DISABLE_COPY(ListsSubscriptions)
public:
    ListsSubscriptions(QObject *parent = 0);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void countChanged(int count);
    void cursorChanged(const QString &cursor);

    void nextCursorChanged(int nextCursor) const;
    void nextCursorStrChanged(const QString &nextCursorStr) const;
    void previousCursorChanged(int previousCursor) const;
    void previousCursorStrChanged(const QString &previousCursorStr) const;

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/subscriptions.json"); }
    void parseDone(const QVariant &result);
};

#endif // LISTSSUBSCRIPTIONS_H
