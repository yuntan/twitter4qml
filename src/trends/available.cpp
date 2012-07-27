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
