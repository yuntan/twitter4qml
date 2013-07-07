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

#ifndef SHOWLISTS_H
#define SHOWLISTS_H

#include "abstractlistsaction.h"

class ShowLists : public AbstractListsAction
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ list_id WRITE list_id NOTIFY list_idChanged)
    Q_PROPERTY(QString slug READ slug WRITE slug NOTIFY slugChanged)
    Q_PROPERTY(QString owner_screen_name READ owner_screen_name WRITE owner_screen_name NOTIFY owner_screen_nameChanged)
    Q_PROPERTY(QString owner_id READ owner_id WRITE owner_id NOTIFY owner_idChanged)

    Q_PROPERTY(QString created_at READ created_at WRITE created_at NOTIFY created_atChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString name READ name WRITE name NOTIFY nameChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString full_name READ full_name WRITE full_name NOTIFY full_nameChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString description READ description WRITE description NOTIFY descriptionChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString mode READ mode WRITE mode NOTIFY modeChanged DESIGNABLE false USER true)
    Q_PROPERTY(bool following READ following WRITE following NOTIFY followingChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantMap user READ user WRITE user NOTIFY userChanged DESIGNABLE false USER true)
    Q_PROPERTY(int member_count READ member_count WRITE member_count NOTIFY member_countChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString id_str READ id_str WRITE id_str NOTIFY id_strChanged DESIGNABLE false USER true)
    Q_PROPERTY(int subscriber_count READ subscriber_count WRITE subscriber_count NOTIFY subscriber_countChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString uri READ uri WRITE uri NOTIFY uriChanged DESIGNABLE false USER true)
    Q_DISABLE_COPY(ShowLists)
public:
    explicit ShowLists(QObject *parent = 0);

public slots:
    void exec();

signals:
    void list_idChanged(const QString &list_id);
    void slugChanged(const QString &slug);
    void owner_screen_nameChanged(const QString &owner_screen_name);
    void owner_idChanged(const QString &owner_id);

    void created_atChanged(const QString &created_at);
    void nameChanged(const QString &name);
    void full_nameChanged(const QString &full_name);
    void descriptionChanged(const QString &description);
    void modeChanged(const QString &mode);
    void followingChanged(bool following);
    void userChanged(const QVariantMap &user);
    void member_countChanged(int member_count);
    void id_strChanged(const QString &id_str);
    void subscriber_countChanged(int subscriber_count);
    void uriChanged(const QString &uri);

protected:
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/lists/show.json"); }
    QString httpMethod() const { return "GET"; }

private:
    ADD_PROPERTY(const QString &, created_at, QString)
    ADD_PROPERTY(const QString &, full_name, QString)
    ADD_PROPERTY(bool, following, bool)
    ADD_PROPERTY(const QVariantMap &, user, QVariantMap)
    ADD_PROPERTY(int, member_count, int)
    ADD_PROPERTY(const QString &, id_str, QString)
    ADD_PROPERTY(int, subscriber_count, int)
    ADD_PROPERTY(const QString &, uri, QString)
};

#endif // SHOWLISTS_H
