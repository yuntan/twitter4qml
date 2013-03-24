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

#ifndef ABSTRACTUSERSMODEL_H
#define ABSTRACTUSERSMODEL_H

#include "abstracttwittermodel.h"

class TWITTER4QML_EXPORT AbstractUsersModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractUsersModel)
public:
    enum Roles {
        ContributorsEnabledRole = Qt::UserRole + 1
        , created_at_role
        , DefaultProfileRole
        , DefaultProfileImageRole
        , DescriptionRole
        , FavouritesCountRole
        , FollowRequestSentRole
        , FollowersCountRole
        , FollowingRole
        , FriendsCountRole
        , GeoEnabledRole
        , id_role
        , id_str_role
        , IsTranslatorRole
        , LangRole
        , ListedCountRole
        , LocationRole
        , name_role
        , NotificationsRole
        , ProfileBackgroundColorRole
        , ProfileBackgroundImageurl_role
        , ProfileBackgroundImageUrlHttpsRole
        , ProfileBackgroundTileRole
        , ProfileImageurl_role
        , ProfileImageUrlHttpsRole
        , ProfileLinkColorRole
        , ProfileSidebarBorderColorRole
        , ProfileSidebarFillColorRole
        , ProfileTextColorRole
        , ProfileUseBackgroundImageRole
        , ProtectedRole
        , screen_nameRole
        , ShowAllInlineMediaRole
        , StatusesCountRole
        , TimeZoneRole
        , url_role
        , UtcOffsetRole
        , VerifiedRole
    };
    explicit AbstractUsersModel(QObject *parent = 0);

    DataManager::DataType dataType() const { return DataManager::UserData; }

public slots:
    void reload();

signals:
    void idChanged(const QString &id);
    void screen_nameChanged(const QString &screen_name);
    void include_entitiesChanged(bool include_entities);
    void countChanged(int count);
    void pageChanged(int page);
    void cursorChanged(const QString &cursor);

    void next_cursorChanged(int next_cursor) const;
    void next_cursor_strChanged(const QString &next_cursor_str) const;
    void previous_cursorChanged(int previous_cursor) const;
    void previous_cursor_strChanged(const QString &previous_cursor_str) const;

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    void parseDone(const QVariant &result);

private:
    ADD_PROPERTY(const QString &, id, QString)
    ADD_PROPERTY(const QString &, screen_name, QString)
    ADD_PROPERTY(bool, include_entities, bool)
    ADD_PROPERTY(int, count, int)
    ADD_PROPERTY(int, page, int)
    ADD_PROPERTY(const QString &, cursor, QString)

    ADD_PROPERTY(int, next_cursor, int)
    ADD_PROPERTY(const QString &, next_cursor_str, QString)
    ADD_PROPERTY(int, previous_cursor, int)
    ADD_PROPERTY(const QString &, previous_cursor_str, QString)
};

#endif // ABSTRACTUSERSMODEL_H
