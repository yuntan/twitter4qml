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

#ifndef ABSTRACTBLOCKACTION_H
#define ABSTRACTBLOCKACTION_H

#include "../tools/abstracttwitteraction.h"

class AbstractBlockAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_DISABLE_COPY(AbstractBlockAction)
public:
    explicit AbstractBlockAction(QObject *parent = 0);
    ~AbstractBlockAction();

    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    const QString &userId() const;
    void setUserId(const QString &userId);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);
    bool skipStatus() const;
    void setSkipStatus(bool skipStatus);

signals:
    void screenNameChanged(const QString &screenName);
    void userIdChanged(const QString &userId);
    void includeEntitiesChanged(bool includeEntities);
    void skipStatusChanged(bool skipStatus);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTBLOCKACTION_H
