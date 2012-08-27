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

#include "abstractidsmodel.h"

class AbstractIdsModel::Private
{
public:
    Private();

    QString id;
    int count;
    int page;
    bool stringifyIds;
};

AbstractIdsModel::Private::Private()
    : count(0)
    , page(0)
    , stringifyIds(true)
{
}

AbstractIdsModel::AbstractIdsModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[IdStrRole] = "id_str";
    setRoleNames(roles);
}

AbstractIdsModel::~AbstractIdsModel()
{
    delete d;
}

AbstractTwitterModel::AuthorizeBy AbstractIdsModel::authenticationMethod() const
{
    return AuthorizeByUrl;
}

QString AbstractIdsModel::httpMethod() const
{
    return "GET";
}

void AbstractIdsModel::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Int) {
                QVariantMap map;
                map.insert("id", result.toInt());
                map.insert("id_str", result.toString());
                addData(map);
            } else if (result.type() == QVariant::String) {
                QVariantMap map;
                map.insert("id", result.toInt());
                map.insert("id_str", result.toString());
                addData(map);
            } else {
                DEBUG() << result.type() << result;
            }
        }
    } else {
        DEBUG() << result.type() << result;
    }
}

const QString &AbstractIdsModel::id() const
{
    return d->id;
}

void AbstractIdsModel::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

int AbstractIdsModel::count() const
{
    return d->count;
}

void AbstractIdsModel::setCount(int count)
{
    if (d->count == count) return;
    d->count = count;
    emit countChanged(count);
}

int AbstractIdsModel::page() const
{
    return d->page;
}

void AbstractIdsModel::setPage(int page)
{
    if (d->page == page) return;
    d->page = page;
    emit pageChanged(page);
}

bool AbstractIdsModel::stringifyIds() const
{
    return d->stringifyIds;
}

void AbstractIdsModel::setStringifyIds(bool stringifyIds)
{
    if (d->stringifyIds == stringifyIds) return;
    d->stringifyIds = stringifyIds;
    emit stringifyIdsChanged(stringifyIds);
}
