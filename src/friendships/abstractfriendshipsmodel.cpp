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

#include "abstractfriendshipsmodel.h"

#include <QtCore/QDebug>

#define DEBUG() qDebug() << __PRETTY_FUNCTION__ << __LINE__

class AbstractFriendshipsModel::Private
{
public:
    Private();

    QString sinceId;
    QString maxId;
    int count;
    int page;
    bool includeEntities;
};

AbstractFriendshipsModel::Private::Private()
    : count(0)
    , page(0)
    , includeEntities(true)
{
}

AbstractFriendshipsModel::AbstractFriendshipsModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[CreatedAtRole] = "created_at";
    roles[EntitiesRole] = "entities";
    roles[IdRole] = "id_str";
    roles[RecipientRole] = "recipient";
    roles[RecipientIdRole] = "recipient_id";
    roles[RecipientScreenNameRole] = "recipient_screen_name";
    roles[SenderRole] = "sender";
    roles[SenderIdRole] = "sender_id";
    roles[SenderScreenNameRole] = "sender_screen_name";
    roles[TextRole] = "text";
    setRoleNames(roles);
}

AbstractFriendshipsModel::~AbstractFriendshipsModel()
{
    delete d;
}


AbstractTwitterModel::AuthorizeBy AbstractFriendshipsModel::authenticationMethod() const
{
    return AuthorizeByUrl;
}

QString AbstractFriendshipsModel::httpMethod() const
{
    return "GET";
}

void AbstractFriendshipsModel::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                addData(result.toMap());
            }
        }
    }
}

const QString &AbstractFriendshipsModel::sinceId() const

{
    return d->sinceId;
}

void AbstractFriendshipsModel::setSinceId(const QString &sinceId)
{
    if (d->sinceId == sinceId) return;
    d->sinceId = sinceId;
    emit sinceIdChanged(sinceId);
}

const QString &AbstractFriendshipsModel::maxId() const
{
    return d->maxId;
}

void AbstractFriendshipsModel::setMaxId(const QString &maxId)
{
    if (d->maxId == maxId) return;
    d->maxId = maxId;
    emit maxIdChanged(maxId);
}

int AbstractFriendshipsModel::count() const
{
    return d->count;
}

void AbstractFriendshipsModel::setCount(int count)
{
    if (d->count == count) return;
    d->count = count;
    emit countChanged(count);
}

int AbstractFriendshipsModel::page() const
{
    return d->page;
}

void AbstractFriendshipsModel::setPage(int page)
{
    if (d->page == page) return;
    d->page = page;
    emit pageChanged(page);
}

bool AbstractFriendshipsModel::includeEntities() const
{
    return d->includeEntities;
}

void AbstractFriendshipsModel::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}
