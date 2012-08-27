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

#include "geosearch.h"

#include <QtCore/qnumeric.h>
#include <QtCore/QTimer>

class GeoSearch::Private
{
public:
    Private();
    double latitude;
    double longitude;
    QString query;
    QString ip;
    QString granularity;
    QString accuracy;
    int maxResults;
    QString containedWithin;

    QTimer timer;
};

GeoSearch::Private::Private()
    : latitude(0)
    , longitude(0)
    , maxResults(0)
{
    timer.setInterval(0);
    timer.setSingleShot(true);
}

GeoSearch::GeoSearch(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[AttrubutesRole] = "attributes";
    roles[BoundingBoxRole] = "bounding_box";
    roles[ContainedWithinRole] = "contained_within";
    roles[CountryRole] = "country";
    roles[CountryCodeRole] = "countryCode";
    roles[FullNameRole] = "full_name";
    roles[IdRole] = "id";
    roles[IdStrRole] = "id_str";
    roles[NameRole] = "name";
    roles[PlaceTypeRole] = "placeType";
    roles[UrlRole] = "url";
    setRoleNames(roles);
    connect(&d->timer, SIGNAL(timeout()), this, SLOT(reload()));
    connect(this, SIGNAL(latitudeChanged(double)), &d->timer, SLOT(start()));
    connect(this, SIGNAL(longitudeChanged(double)), &d->timer, SLOT(start()));
    connect(this, SIGNAL(queryChanged(QString)), &d->timer, SLOT(start()));
    connect(this, SIGNAL(accuracyChanged(QString)), &d->timer, SLOT(start()));
}

GeoSearch::~GeoSearch()
{
    delete d;
}

void GeoSearch::reload()
{
    if (qIsNaN(latitude())) return;
    if (qIsNaN(longitude())) return;
    if (qFuzzyCompare(latitude(), 0.0)) return;
    if (qFuzzyCompare(longitude(), 0.0)) return;

    DEBUG() << latitude() << longitude();
    AbstractTwitterModel::reload();
}

void GeoSearch::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::Map && result.toMap().value("result").type() == QVariant::Map) {
        QVariantList array = result.toMap().value("result").toMap().value("places").toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                QVariantMap map = result.toMap();
                map.insert("id_str", map.value("id").toString());
                addData(map);
            }
        }
    }
}

double GeoSearch::latitude() const
{
    return d->latitude;
}

void GeoSearch::setLatitude(double latitude)
{
    if (d->latitude == latitude) return;
    d->latitude = latitude;
    emit latitudeChanged(latitude);
}

double GeoSearch::longitude() const
{
    return d->longitude;
}

void GeoSearch::setLongitude(double longitude)
{
    if (d->longitude == longitude) return;
    d->longitude = longitude;
    emit longitudeChanged(longitude);
}

const QString &GeoSearch::query() const
{
    return d->query;
}

void GeoSearch::setQuery(const QString &query)
{
    if (d->query == query) return;
    d->query = query;
    emit queryChanged(query);
}

const QString &GeoSearch::ip() const
{
    return d->ip;
}

void GeoSearch::setIp(const QString &ip)
{
    if (d->ip == ip) return;
    d->ip = ip;
    emit ipChanged(ip);
}

const QString &GeoSearch::granularity() const
{
    return d->granularity;
}

void GeoSearch::setGranularity(const QString &granularity)
{
    if (d->granularity == granularity) return;
    d->granularity = granularity;
    emit granularityChanged(granularity);
}

const QString &GeoSearch::accuracy() const
{
    return d->accuracy;
}

void GeoSearch::setAccuracy(const QString &accuracy)
{
    if (d->accuracy == accuracy) return;
    d->accuracy = accuracy;
    emit accuracyChanged(accuracy);
}

int GeoSearch::maxResults() const
{
    return d->maxResults;
}

void GeoSearch::setMaxResults(int maxResults)
{
    if (d->maxResults == maxResults) return;
    d->maxResults = maxResults;
    emit maxResultsChanged(maxResults);
}

const QString &GeoSearch::containedWithin() const
{
    return d->containedWithin;
}

void GeoSearch::setContainedWithin(const QString &containedWithin)
{
    if (d->containedWithin == containedWithin) return;
    d->containedWithin = containedWithin;
    emit containedWithinChanged(containedWithin);
}
