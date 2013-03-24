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

#ifndef ABSTRACTFRIENDSHIPIDSMODEL_H
#define ABSTRACTFRIENDSHIPIDSMODEL_H

#include "abstracttwittermodel.h"

class TWITTER4QML_EXPORT AbstractFriendshipIdsModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(int next_cursor READ next_cursor NOTIFY next_cursorChanged DESIGNABLE false)
    Q_PROPERTY(QString next_cursor_str READ next_cursor_str NOTIFY next_cursor_strChanged DESIGNABLE false)
    Q_PROPERTY(int previous_cursor READ previous_cursor NOTIFY previous_cursorChanged DESIGNABLE false)
    Q_PROPERTY(QString previous_cursor_str READ previous_cursor_str NOTIFY previous_cursor_strChanged DESIGNABLE false)
    Q_DISABLE_COPY(AbstractFriendshipIdsModel)
public:
    enum Roles {
        id_role = Qt::UserRole + 1
        , id_str_role
    };
    explicit AbstractFriendshipIdsModel(QObject *parent = 0);
    ~AbstractFriendshipIdsModel();

public slots:
    virtual void reload();

signals:
    void user_idChanged(const QString &user_id);
    void screen_nameChanged(const QString &screen_name);
    void cursorChanged(const QString &cursor);
    void stringify_idsChanged(bool stringify_ids);
    void countChanged(int count);

    void next_cursorChanged(int next_cursor) const;
    void next_cursor_strChanged(const QString &next_cursor_str) const;
    void previous_cursorChanged(int previous_cursor) const;
    void previous_cursor_strChanged(const QString &previous_cursor_str) const;

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;

    ADD_PROPERTY(const QString &, user_id, QString)
    ADD_PROPERTY(const QString &, screen_name, QString)
    ADD_PROPERTY(const QString &, cursor, QString)
    ADD_PROPERTY(bool, stringify_ids, bool)
    ADD_PROPERTY(int, count, int)

    ADD_PROPERTY(int, next_cursor, int)
    ADD_PROPERTY(const QString &, next_cursor_str, QString)
    ADD_PROPERTY(int, previous_cursor, int)
    ADD_PROPERTY(const QString &, previous_cursor_str, QString)
};

#endif // ABSTRACTFRIENDSHIPIDSMODEL_H
