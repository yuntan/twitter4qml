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

#ifndef LISTSTATUSES_H
#define LISTSTATUSES_H

#include "../statuses/abstractstatusesmodel.h"

class ListStatuses : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ id WRITE id NOTIFY idChanged)
    Q_PROPERTY(QString slug READ slug WRITE slug NOTIFY slugChanged)
    Q_PROPERTY(QString owner_screen_name READ screen_name WRITE screen_name NOTIFY screen_nameChanged)
    Q_PROPERTY(QString owner_id READ user_id WRITE user_id NOTIFY user_idChanged)
    Q_PROPERTY(QString since_id READ since_id WRITE since_id NOTIFY since_idChanged)
    Q_PROPERTY(QString max_id READ max_id WRITE max_id NOTIFY max_idChanged)
    Q_PROPERTY(int count READ count WRITE count NOTIFY countChanged)
    Q_PROPERTY(bool include_entities READ include_entities WRITE include_entities NOTIFY include_entitiesChanged)
    Q_PROPERTY(bool include_rts READ include_rts WRITE include_rts NOTIFY include_rtsChanged)
    Q_DISABLE_COPY(ListStatuses)
public:
    explicit ListStatuses(QObject *parent = 0);

signals:
    void idChanged(const QString &id);
    void slugChanged(const QString &slug);
    void screen_nameChanged(const QString &screen_name);
    void user_idChanged(const QString &user_id);
    void since_idChanged(const QString &since_id);
    void max_idChanged(const QString &max_id);
    void countChanged(int count);
    void include_entitiesChanged(bool include_entities);
    void include_rtsChanged(bool include_rts);

protected:
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/lists/statuses.json"); }

    ADD_PROPERTY(const QString &, slug, QString)
    ADD_PROPERTY(bool, include_rts, bool)
};

#endif // LISTSTATUSES_H
