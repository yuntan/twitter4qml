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

#include "abstractstatusesmodel.h"
#include "status.h"

AbstractStatusesModel::AbstractStatusesModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , m_count(0)
    , m_trim_user(false)
    , m_include_entities(true)
    , m_contributor_details(false)
{
    QHash<int, QByteArray> roles;
    roles[ContributorsRole] = "contributors";
    roles[CoordinatesRole] = "coordinates";
    roles[created_at_role] = "created_at";
    roles[EntitiesRole] = "entities";
    roles[FavoritedRole] = "favorited";
    roles[GeoRole] = "geo";
    roles[id_role] = "id";
    roles[id_str_role] = "id_str";
    roles[in_reply_to_screen_nameRole] = "in_reply_to_screen_name";
    roles[in_reply_to_status_idRole] = "in_reply_to_status_id_str";
    roles[InReplyTouser_idRole] = "in_reply_to_user_id_str";
    roles[PlaceRole] = "place";
    roles[possibly_sensitiveRole] = "possibly_sensitive";
    roles[retweet_countRole] = "retweet_count";
    roles[RetweetedRole] = "retweeted";
    roles[retweeted_statusRole] = "retweeted_status";
    roles[SourceRole] = "source";
    roles[TextRole] = "text";
    roles[plain_textRole] = "plain_text";
    roles[rich_textRole] = "rich_text";
    roles[TruncatedRole] = "truncated";
    roles[UserRole] = "user";
    roles[MediaRole] = "media";
    setRoleNames(roles);
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
