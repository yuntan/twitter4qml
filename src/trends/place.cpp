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

#include "place.h"
#include <QtCore/qalgorithms.h>

Place::Place(QObject *parent)
    : AbstractTwitterModel(parent)
    , m_id(0)
    , m_exclude(false)
{
    QHash<int, QByteArray> roles;
    roles[query_role] = "query";
    roles[name_role] = "name";
    roles[PromotedContentRole] = "promoted_content";
    roles[EventsRole] = "events";
    roles[url_role] = "url";
    setRoleNames(roles);
//    connect(this, SIGNAL(idChanged(int)), this, SLOT(reload()));
}

void Place::reload()
{
    if (id() > 0) {
        AbstractTwitterModel::reload();
    }
}

void Place::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                QVariantMap map = result.toMap();
                if (map.contains("trends") && map.value("trends").type() == QVariant::List) {
                    QVariantList trends = map.value("trends").toList();
                    QAlgorithmsPrivate::qReverse(trends.begin(), trends.end());
                    foreach (const QVariant &trend, trends) {
                        QVariantMap t = trend.toMap();
                        t.insert("id_str", t.value("name").toString());
                        addData(t);
                    }
                }
            }
        }
    }
}
