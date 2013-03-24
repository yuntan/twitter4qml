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

#include "userstream.h"
#include "status.h"
#include "../directmessages/directmessage.h"

class UserStream::Private
{
public:
    Private();
    QString delimited;
    QString replies;
    QStringList friends;
};

UserStream::Private::Private() : delimited("length") {}

UserStream::UserStream(QObject *parent)
    : AbstractStatusesModel(parent)
    , d(new Private)
{
    setPushOrder(PushOlderToNewer);
}

UserStream::~UserStream()
{
    delete d;
}

void UserStream::parseDone(const QVariant &result)
{
    switch (result.type()) {
    case QVariant::Map: {
        QVariantMap object = result.toMap();
        if (object.keys().contains("text")) {
            addData(Status::parse(result.toMap()));
        } else if (object.keys().contains("friends")) {
            d->friends.clear();
            QVariantList list = object.value("friends").toList();
            foreach (const QVariant &id, list) {
                d->friends.append(id.toString());
            }
            emit friendsChanged(d->friends);
        } else if (object.keys().contains("event")) {
            DEBUG() << object.value("event").toString() << object;
            if (object.value("event").toString() == "follow") {
                emit followedBy(Status::parse(object));
            } else if (object.value("event").toString() == "favorite") {
                emit favorited(Status::parse(object));
            } else if (object.value("event").toString() == "unfavorite") {
                emit unfavorited(Status::parse(object));
            } else {
                DEBUG() << object.value("event").toString() << object;
            }
        } else if (object.keys().contains("direct_message")) {
            QVariantMap directMessage = object.value("direct_message").toMap();
            DEBUG() << directMessage;
            DataManager::instance()->addData(DataManager::DirectMessageData, directMessage.value("id_str").toString(), DirectMessage::parse(directMessage));
        } else if (object.keys().contains("delete")) {
            DataManager::instance()->removeData(DataManager::StatusData, object.value("delete").toMap().value("status").toMap().value("id_str").toString());
        } else {
            DEBUG() << object;
        }
    }
        break;
    default:
        DEBUG() << result;
        break;
    }
}

const QString &UserStream::delimited() const
{
    return d->delimited;
}

void UserStream::setDelimited(const QString &delimited)
{
    if (d->delimited == delimited) return;
    d->delimited = delimited;
    emit delimitedChanged(delimited);
}

const QString &UserStream::replies() const
{
    return d->replies;
}

void UserStream::setReplies(const QString &replies)
{
    if (d->replies == replies) return;
    d->replies = replies;
    emit repliesChanged(replies);
}

const QStringList &UserStream::friends() const
{
    return d->friends;
}
