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

#include "available.h"

class Available::Private
{
public:
    Private();
    double latitude;
    double longitude;
};

Available::Private::Private()
    : latitude(0)
    , longitude(0)
{
}

Available::Available(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[CountryRole] = "country";
    roles[CountryCodeRole] = "countryCode";
    roles[NameRole] = "name";
    roles[ParentIdRole] = "parentid";
    roles[PlaceTypeRole] = "placeType";
    roles[UrlRole] = "url";
    roles[WoeidRole] = "woeid";
    setRoleNames(roles);
    connect(this, SIGNAL(latitudeChanged(double)), this, SLOT(reload()));
    connect(this, SIGNAL(longitudeChanged(double)), this, SLOT(reload()));
}

Available::~Available()
{
    delete d;
}

void Available::reload()
{
    if (!qFuzzyCompare(latitude(), 0.0) || !qFuzzyCompare(longitude(), 0.0)) {
        AbstractTwitterModel::reload();
    }
}

void Available::parseDone(const QVariant &result)
{
    DEBUG() << result;
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                QVariantMap map = result.toMap();
                map.insert("id_str", map.value("name").toString());
                addData(map);
            }
        }
    }
}

double Available::latitude() const
{
    return d->latitude;
}

void Available::setLatitude(double latitude)
{
    if (d->latitude == latitude) return;
    d->latitude = latitude;
    emit latitudeChanged(latitude);
}

double Available::longitude() const
{
    return d->longitude;
}

void Available::setLongitude(double longitude)
{
    if (d->longitude == longitude) return;
    d->longitude = longitude;
    emit longitudeChanged(longitude);
}
