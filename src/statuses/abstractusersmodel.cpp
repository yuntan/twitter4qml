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

#include "abstractusersmodel.h"

class AbstractUsersModel::Private
{
public:
    Private();

    QString id;
    int count;
    int page;
};

AbstractUsersModel::Private::Private()
    : count(0)
    , page(0)
{
}

AbstractUsersModel::AbstractUsersModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[ContributorsEnabled] = "contributors_enabled";
    roles[CreatedAtRole] = "created_at";
    roles[DefaultProfileRole] = "default_profile";
    roles[DefaultProfileImageRole] = "default_profile_image";
    roles[DescriptionRole] = "description";
    roles[FavouritesCountRole] = "favourites_count";
    roles[FollowRequestSentRole] = "follow_request_sent";
    roles[FollowersCountRole] = "followers_count";
    roles[FollowingRole] = "following";
    roles[FriendsCountRole] = "friends_count";
    roles[GeoEnabledRole] = "geo_enabled";
    roles[IdRole] = "id";
    roles[IdStrRole] = "id_str";
    roles[IsTranslatorRole] = "is_translator";
    roles[LangRole] = "lang";
    roles[ListedCountRole] = "listed_count";
    roles[LocationRole] = "location";
    roles[NameRole] = "name";
    roles[NotificationsRole] = "notifications";
    roles[ProfileBackgroundColorRole] = "profile_background_color";
    roles[ProfileBackgroundImageUrlRole] = "profile_background_image_url";
    roles[ProfileBackgroundImageUrlHttpsRole] = "profile_background_image_url_https";
    roles[ProfileBackgroundTileRole] = "profile_background_tile";
    roles[ProfileImageUrlRole] = "profile_image_url";
    roles[ProfileImageUrlHttpsRole] = "profile_image_url_https";
    roles[ProfileLinkColorRole] = "profile_link_color";
    roles[ProfileSidebarBorderColorRole] = "profile_sidebar_border_color";
    roles[ProfileSidebarFillColorRole] = "profile_sidebar_fill_color";
    roles[ProfileTextColorRole] = "profile_text_color";
    roles[ProfileUseBackgroundImageRole] = "profile_use_background_image";
    roles[ProtectedRole] = "protected";
    roles[ScreenNameRole] = "screen_name";
    roles[ShowAllInlineMediaRole] = "show_all_inline_media";
    roles[StatusRole] = "status";
    roles[StatusCountRole] = "statuses_count";
    roles[TimeZoneRole] = "time_zone";
    roles[UrlRole] = "url";
    roles[UtcOffsetRole] = "utc_offset";
    roles[VerifiedRole] = "verified";
    setRoleNames(roles);
}

AbstractUsersModel::~AbstractUsersModel()
{
    delete d;
}

AbstractTwitterModel::AuthorizeBy AbstractUsersModel::authenticationMethod() const
{
    return AuthorizeByUrl;
}

QString AbstractUsersModel::httpMethod() const
{
    return "GET";
}

void AbstractUsersModel::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                addData(result.toMap());
            }
        }
    }
}

const QString &AbstractUsersModel::id() const
{
    return d->id;
}

void AbstractUsersModel::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

int AbstractUsersModel::count() const
{
    return d->count;
}

void AbstractUsersModel::setCount(int count)
{
    if (d->count == count) return;
    d->count = count;
    emit countChanged(count);
}

int AbstractUsersModel::page() const
{
    return d->page;
}

void AbstractUsersModel::setPage(int page)
{
    if (d->page == page) return;
    d->page = page;
    emit pageChanged(page);
}
