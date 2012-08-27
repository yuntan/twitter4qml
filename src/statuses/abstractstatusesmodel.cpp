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

#include "abstractstatusesmodel.h"
#include "status.h"

class AbstractStatusesModel::Private
{
public:
    Private();

    QString userId;
    QString screenName;
    QString id;
    int count;
    QString sinceId;
    QString maxId;
    int page;
    bool trimUser;
    bool includeRts;
    bool excludeReplies;
    bool includeEntities;
    bool contributorDetails;
    QString listId;
    int perPage;
};

AbstractStatusesModel::Private::Private()
    : count(0)
    , page(0)
    , trimUser(false)
    , includeRts(true)
    , excludeReplies(false)
    , includeEntities(true)
    , contributorDetails(false)
    , perPage(0)
{
}

AbstractStatusesModel::AbstractStatusesModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[ContributorsRole] = "contributors";
    roles[CoordinatesRole] = "coordinates";
    roles[CreatedAtRole] = "created_at";
    roles[EntitiesRole] = "entities";
    roles[FavoritedRole] = "favorited";
    roles[GeoRole] = "geo";
    roles[IdRole] = "id";
    roles[IdStrRole] = "id_str";
    roles[InReplyToScreenNameRole] = "in_reply_to_screen_name";
    roles[InReplyToStatusIdRole] = "in_reply_to_status_id_str";
    roles[InReplyToUserIdRole] = "in_reply_to_user_id_str";
    roles[PlaceRole] = "place";
    roles[PossiblySensitiveRole] = "possibly_sensitive";
    roles[RetweetCountRole] = "retweet_count";
    roles[RetweetedRole] = "retweeted";
    roles[RetweetedStatusRole] = "retweeted_status";
    roles[SourceRole] = "source";
    roles[TextRole] = "text";
    roles[PlainTextRole] = "plain_text";
    roles[RichTextRole] = "rich_text";
    roles[TruncatedRole] = "truncated";
    roles[UserRole] = "user";
    roles[MediaRole] = "media";
    setRoleNames(roles);
}

AbstractStatusesModel::~AbstractStatusesModel()
{
    delete d;
}

void AbstractStatusesModel::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                addData(Status::parse(result.toMap()));
            }
        }
    }
}

const QString &AbstractStatusesModel::userId() const
{
    return d->userId;
}

void AbstractStatusesModel::setUserId(const QString &userId)
{
    if (d->userId == userId) return;
    d->userId = userId;
    emit userIdChanged(userId);
}

const QString &AbstractStatusesModel::screenName() const
{
    return d->screenName;
}

void AbstractStatusesModel::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

const QString &AbstractStatusesModel::id() const
{
    return d->id;
}

void AbstractStatusesModel::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

int AbstractStatusesModel::count() const
{
    return d->count;
}

void AbstractStatusesModel::setCount(int count)
{
    if (d->count == count) return;
    d->count = count;
    emit countChanged(count);
}

const QString &AbstractStatusesModel::sinceId() const
{
    return d->sinceId;
}

void AbstractStatusesModel::setSinceId(const QString &sinceId)
{
    if (d->sinceId == sinceId) return;
    d->sinceId = sinceId;
    emit sinceIdChanged(sinceId);
}

const QString &AbstractStatusesModel::maxId() const
{
    return d->maxId;
}

void AbstractStatusesModel::setMaxId(const QString &maxId)
{
    if (d->maxId == maxId) return;
    d->maxId = maxId;
    emit maxIdChanged(maxId);
}

int AbstractStatusesModel::page() const
{
    return d->page;
}

void AbstractStatusesModel::setPage(int page)
{
    if (d->page == page) return;
    d->page = page;
    emit pageChanged(page);
}

bool AbstractStatusesModel::trimUser() const
{
    return d->trimUser;
}

void AbstractStatusesModel::setTrimUser(bool trimUser)
{
    if (d->trimUser == trimUser) return;
    d->trimUser = trimUser;
    emit trimUserChanged(trimUser);
}

bool AbstractStatusesModel::includeRts() const
{
    return d->includeRts;
}

void AbstractStatusesModel::setIncludeRts(bool includeRts)
{
    if (d->includeRts == includeRts) return;
    d->includeRts = includeRts;
    emit includeRtsChanged(includeRts);
}

bool AbstractStatusesModel::excludeReplies() const
{
    return d->excludeReplies;
}

void AbstractStatusesModel::setExcludeReplies(bool excludeReplies)
{
    if (d->excludeReplies == excludeReplies) return;
    d->excludeReplies = excludeReplies;
    emit excludeRepliesChanged(excludeReplies);
}

bool AbstractStatusesModel::includeEntities() const
{
    return d->includeEntities;
}

void AbstractStatusesModel::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}

bool AbstractStatusesModel::contributorDetails() const
{
    return d->contributorDetails;
}

void AbstractStatusesModel::setContributorDetails(bool contributorDetails)
{
    if (d->contributorDetails == contributorDetails) return;
    d->contributorDetails = contributorDetails;
    emit contributorDetailsChanged(contributorDetails);
}

const QString &AbstractStatusesModel::listId() const
{
    return d->listId;
}

void AbstractStatusesModel::setListId(const QString &listId)
{
    if (d->listId == listId) return;
    d->listId = listId;
    emit listIdChanged(listId);
}

int AbstractStatusesModel::perPage() const
{
    return d->perPage;
}

void AbstractStatusesModel::setPerPage(int perPage)
{
    if (d->perPage == perPage) return;
    d->perPage = perPage;
    emit perPageChanged(perPage);
}

