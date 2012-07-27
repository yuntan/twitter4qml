#include "reversegeocode.h"

#include <QtCore/qnumeric.h>
#include <QtCore/QTimer>

class ReverseGeocode::Private
{
public:
    Private();
    double latitude;
    double longitude;
    QString granularity;
    QString accuracy;
    int maxResults;

    QTimer timer;
};

ReverseGeocode::Private::Private()
    : latitude(0)
    , longitude(0)
    , maxResults(0)
{
    timer.setInterval(0);
    timer.setSingleShot(true);
}

ReverseGeocode::ReverseGeocode(QObject *parent)
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

    DEBUG() << latitude() << longitude();
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

double ReverseGeocode::latitude() const
{
    return d->latitude;
}

void ReverseGeocode::setLatitude(double latitude)
{
    if (d->latitude == latitude) return;
    d->latitude = latitude;
    emit latitudeChanged(latitude);
}

double ReverseGeocode::longitude() const
{
    return d->longitude;
}

void ReverseGeocode::setLongitude(double longitude)
{
    if (d->longitude == longitude) return;
    d->longitude = longitude;
    emit longitudeChanged(longitude);
}

const QString &ReverseGeocode::granularity() const
{
    return d->granularity;
}

void ReverseGeocode::setGranularity(const QString &granularity)
{
    if (d->granularity == granularity) return;
    d->granularity = granularity;
    emit granularityChanged(granularity);
}

const QString &ReverseGeocode::accuracy() const
{
    return d->accuracy;
}

void ReverseGeocode::setAccuracy(const QString &accuracy)
{
    if (d->accuracy == accuracy) return;
    d->accuracy = accuracy;
    emit accuracyChanged(accuracy);
}

int ReverseGeocode::maxResults() const
{
    return d->maxResults;
}

void ReverseGeocode::setMaxResults(int maxResults)
{
    if (d->maxResults == maxResults) return;
    d->maxResults = maxResults;
    emit maxResultsChanged(maxResults);
}
