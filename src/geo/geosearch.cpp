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
