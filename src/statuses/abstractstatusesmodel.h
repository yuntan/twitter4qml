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

#ifndef ABSTRACTSTATUSESMODEL_H
#define ABSTRACTSTATUSESMODEL_H

#include "../tools/abstracttwittermodel.h"

class AbstractStatusesModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractStatusesModel)
public:
    enum Roles {
        ContributorsRole = Qt::UserRole + 1
        , CoordinatesRole
        , created_at_role
        , EntitiesRole
        , FavoritedRole
        , GeoRole
        , id_role
        , id_str_role
        , in_reply_to_screen_nameRole
        , in_reply_to_status_idRole
        , InReplyTouser_idRole
        , PlaceRole
        , possibly_sensitiveRole
        , retweet_countRole
        , RetweetedRole
        , retweeted_statusRole
        , SourceRole
        , TextRole
        , plain_textRole
        , rich_textRole
        , TruncatedRole
        , UserRole
        , MediaRole
    };
    explicit AbstractStatusesModel(QObject *parent = 0);

    DataManager::DataType dataType() const { return DataManager::StatusData; }

signals:
    void user_idChanged(const QString &user_id);
    void screen_nameChanged(const QString &screen_name);
    void idChanged(const QString &id);
    void countChanged(int count);
    void since_idChanged(const QString &since_id);
    void max_idChanged(const QString &max_id);
    void trim_userChanged(bool trim_user);
    void include_entitiesChanged(bool include_entities);
    void contributor_detailsChanged(bool contributor_details);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    void parseDone(const QVariant &result);

private:
    ADD_PROPERTY(const QString &, user_id, QString)
    ADD_PROPERTY(const QString &, screen_name, QString)
    ADD_PROPERTY(const QString &, id, QString)
    ADD_PROPERTY(int, count, int)
    ADD_PROPERTY(const QString &, since_id, QString)
    ADD_PROPERTY(const QString &, max_id, QString)
    ADD_PROPERTY(bool, trim_user, bool)
    ADD_PROPERTY(bool, include_entities, bool)
    ADD_PROPERTY(bool, contributor_details, bool)
};

#endif // ABSTRACTSTATUSESMODEL_H
