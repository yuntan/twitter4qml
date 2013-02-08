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

#ifndef ABSTRACTFRIENDSHIPACTION_H
#define ABSTRACTFRIENDSHIPACTION_H

#include "../tools/abstracttwitteraction.h"

class AbstractFriendshipAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString screen_name READ screen_name WRITE screen_name NOTIFY screen_nameChanged)
    Q_PROPERTY(QString user_id READ user_id WRITE user_id NOTIFY user_idChanged)
    Q_DISABLE_COPY(AbstractFriendshipAction)
public:
    explicit AbstractFriendshipAction(QObject *parent = 0);

signals:
    void screen_nameChanged(const QString &screen_name);
    void user_idChanged(const QString &user_id);
    void followChanged(bool follow);
//    void include_entitiesChanged(bool include_entities);

private:
    ADD_PROPERTY(const QString &, screen_name, QString)
    ADD_PROPERTY(const QString &, user_id, QString)
    ADD_PROPERTY(bool, follow, bool)
//    ADD_PROPERTY(bool, include_entities, bool)
};

#endif // ABSTRACTFRIENDSHIPACTION_H
