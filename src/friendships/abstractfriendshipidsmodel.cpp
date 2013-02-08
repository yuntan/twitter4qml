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

#include "abstractfriendshipidsmodel.h"

#include <QtCore/QTimer>

class AbstractFriendshipIdsModel::Private
{
public:
    QTimer timer;
};

AbstractFriendshipIdsModel::AbstractFriendshipIdsModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
    , m_stringify_ids(true)
    , m_count(0)
    , m_next_cursor(0)
    , m_previous_cursor(0)
{
    QHash<int, QByteArray> roles;
    roles[id_role] = "id";
    roles[id_str_role] = "id_str";
    setRoleNames(roles);

    connect(&d->timer, SIGNAL(timeout()), this, SLOT(reload()));
    d->timer.setSingleShot(true);
    d->timer.setInterval(0);

    connect(this, SIGNAL(user_idChanged(QString)), &d->timer, SLOT(start()));
    connect(this, SIGNAL(screen_nameChanged(QString)), &d->timer, SLOT(start()));
}

AbstractFriendshipIdsModel::~AbstractFriendshipIdsModel()
{
    delete d;
}

void AbstractFriendshipIdsModel::reload() {
    if (!user_id().isEmpty() || !screen_name().isEmpty()) {
        AbstractTwitterModel::reload();
    }
}

void AbstractFriendshipIdsModel::parseDone(const QVariant &data)
{
//    DEBUG() << data;
    if (data.type() == QVariant::Map) {
        QVariantMap object = data.toMap();
        if (object.contains("ids") && object.value("ids").type() == QVariant::List) {
            QVariantList results = object.value("ids").toList();
            foreach (const QVariant &result, results) {
                QVariantMap map;
                switch(result.type()) {
                case QVariant::Int:
                    map.insert("id", result);
                    addData(map);
                    break;
                case QVariant::String:
                    map.insert("id_str", result);
                    addData(map);
                    break;
                default:
                    break;
                }
            }
        } else {
            DEBUG() << data;
        }
        if (object.contains("next_cursor"))
            next_cursor(object.value("next_cursor").toInt());
        if (object.contains("next_cursor_str"))
            next_cursor_str(object.value("next_cursor_str").toString());
        if (object.contains("previous_cursor"))
            previous_cursor(object.value("previous_cursor").toInt());
        if (object.contains("previous_cursor_str"))
            previous_cursor_str(object.value("previous_cursor_str").toString());
    }
}
