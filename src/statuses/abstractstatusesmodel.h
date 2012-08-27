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
        , CreatedAtRole
        , EntitiesRole
        , FavoritedRole
        , GeoRole
        , IdRole
        , IdStrRole
        , InReplyToScreenNameRole
        , InReplyToStatusIdRole
        , InReplyToUserIdRole
        , PlaceRole
        , PossiblySensitiveRole
        , RetweetCountRole
        , RetweetedRole
        , RetweetedStatusRole
        , SourceRole
        , TextRole
        , PlainTextRole
        , RichTextRole
        , TruncatedRole
        , UserRole
        , MediaRole
    };
    explicit AbstractStatusesModel(QObject *parent = 0);
    ~AbstractStatusesModel();

    const QString &userId() const;
    void setUserId(const QString &userId);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    const QString &id() const;
    void setId(const QString &id);
    int count() const;
    void setCount(int count);
    const QString &sinceId() const;
    void setSinceId(const QString &sinceId);
    const QString &maxId() const;
    void setMaxId(const QString &maxId);
    int page() const;
    void setPage(int page);
    bool trimUser() const;
    void setTrimUser(bool trimUser);
    bool includeRts() const;
    void setIncludeRts(bool includeRts);
    bool excludeReplies() const;
    void setExcludeReplies(bool excludeReplies);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);
    bool contributorDetails() const;
    void setContributorDetails(bool contributorDetails);
    const QString &listId() const;
    void setListId(const QString &listId);
    int perPage() const;
    void setPerPage(int perPage);

    DataManager::DataType dataType() const { return DataManager::StatusData; }

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void idChanged(const QString &id);
    void countChanged(int count);
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void pageChanged(int page);
    void trimUserChanged(bool trimUser);
    void includeRtsChanged(bool includeRts);
    void excludeRepliesChanged(bool excludeReplies);
    void includeEntitiesChanged(bool includeEntities);
    void contributorDetailsChanged(bool contributorDetails);
    void listIdChanged(const QString &listId);
    void perPageChanged(int perPage);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTSTATUSESMODEL_H
