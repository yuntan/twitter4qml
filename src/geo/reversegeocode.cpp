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

#include "reversegeocode.h"

#include <QtCore/qnumeric.h>
#include <QtCore/QTimer>

class ReverseGeocode::Private
{
public:
    Private();
    QTimer timer;
};

ReverseGeocode::Private::Private()
{
    timer.setInterval(0);
    timer.setSingleShot(true);
}

ReverseGeocode::ReverseGeocode(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
    , m_latitude(0)
    , m_longitude(0)
    , m_max_results(0)
{
    QHash<int, QByteArray> roles;
    roles[attrubutes_role] = "attributes";
    roles[bounding_box_role] = "bounding_box";
    roles[contained_within_role] = "contained_within";
    roles[country_role] = "country";
    roles[country_code_role] = "countryCode";
    roles[full_name_role] = "full_name";
    roles[id_role] = "id";
    roles[id_str_role] = "id_str";
    roles[name_role] = "name";
    roles[place_type_role] = "placeType";
    roles[url_role] = "url";
    setRoleNames(roles);
    connect(&d->timer, SIGNAL(timeout()), this, SLOT(reload()));
    connect(this, SIGNAL(latitudeChanged(double)), &d->timer, SLOT(start()));
    connect(this, SIGNAL(longitudeChanged(double)), &d->timer, SLOT(start()));
    connect(this, SIGNAL(accuracyChanged(QString)), &d->timer, SLOT(start()));
}

ReverseGeocode::~ReverseGeocode()
{
    delete d;
}

void ReverseGeocode::reload()
{
    if (qIsNaN(latitude())) return;
    if (qIsNaN(longitude())) return;
    if (qFuzzyCompare(latitude(), 0.0)) return;
    if (qFuzzyCompare(longitude(), 0.0)) return;

    AbstractTwitterModel::reload();
}

void ReverseGeocode::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::Map && result.toMap().value("result").type() == QVariant::Map) {
        QVariantList array = result.toMap().value("result").toMap().value("places").toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                QVariantMap map = result.toMap();
//                DEBUG() << map.keys();
                map.insert("id_str", map.value("id").toString());
                addData(map);
            }
        }
    }
}
