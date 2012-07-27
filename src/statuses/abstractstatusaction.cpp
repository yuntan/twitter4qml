#include "abstractstatusaction.h"

class AbstractStatusAction::Private
{
public:
    Private();

    QString status;
    QVariantList media;
    bool possiblySensitive;
    QString inReplyToStatusId;
    double latitude;
    double longitude;
    QString placeId;
    QString displayCoordinates;
    QString id;
    bool trimUser;
    bool includeEntities;
};

AbstractStatusAction::Private::Private()
    : possiblySensitive(false)
    , trimUser(false)
    , includeEntities(true)
{
}

AbstractStatusAction::AbstractStatusAction(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

AbstractStatusAction::~AbstractStatusAction()
{
    delete d;
}

const QString &AbstractStatusAction::status() const
{
    return d->status;
}

void AbstractStatusAction::setStatus(const QString &status)
{
    if (d->status == status) return;
    d->status = status;
    emit statusChanged(status);
}

const QVariantList &AbstractStatusAction::media() const
{
    return d->media;
}

void AbstractStatusAction::setMedia(const QVariantList &media)
{
    if (d->media == media) return;
    d->media = media;
    emit mediaChanged(media);
}

bool AbstractStatusAction::possiblySensitive() const
{
    return d->possiblySensitive;
}

void AbstractStatusAction::setPossiblySensitive(bool possiblySensitive)
{
    if (d->possiblySensitive == possiblySensitive) return;
    d->possiblySensitive = possiblySensitive;
    emit possiblySensitiveChanged(possiblySensitive);
}

const QString &AbstractStatusAction::inReplyToStatusId() const
{
    return d->inReplyToStatusId;
}

void AbstractStatusAction::setInReplyToStatusId(const QString &inReplyToStatusId)
{
    if (d->inReplyToStatusId == inReplyToStatusId) return;
    d->inReplyToStatusId = inReplyToStatusId;
    emit inReplyToStatusIdChanged(inReplyToStatusId);
}

double AbstractStatusAction::latitude() const
{
    return d->latitude;
}

#include "twitter4qml_global.h"

void AbstractStatusAction::setLatitude(double latitude)
{
    if (d->latitude == latitude) return;
    DEBUG() << latitude;
    d->latitude = latitude;
    emit latitudeChanged(latitude);
}

double AbstractStatusAction::longitude() const
{
    return d->longitude;
}

void AbstractStatusAction::setLongitude(double longitude)
{
    if (d->longitude == longitude) return;
    DEBUG() << longitude;
    d->longitude = longitude;
    emit longitudeChanged(longitude);
}

const QString &AbstractStatusAction::placeId() const
{
    return d->placeId;
}

void AbstractStatusAction::setPlaceId(const QString &placeId)
{
    if (d->placeId == placeId) return;
    d->placeId = placeId;
    emit placeIdChanged(placeId);
}

const QString &AbstractStatusAction::displayCoordinates() const
{
    return d->displayCoordinates;
}

void AbstractStatusAction::setDisplayCoordinates(const QString &displayCoordinates)
{
    if (d->displayCoordinates == displayCoordinates) return;
    d->displayCoordinates = displayCoordinates;
    emit displayCoordinatesChanged(displayCoordinates);
}

const QString &AbstractStatusAction::id() const
{
    return d->id;
}

void AbstractStatusAction::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

bool AbstractStatusAction::trimUser() const
{
    return d->trimUser;
}

void AbstractStatusAction::setTrimUser(bool trimUser)
{
    if (d->trimUser == trimUser) return;
    d->trimUser = trimUser;
    emit trimUserChanged(trimUser);
}

bool AbstractStatusAction::includeEntities() const
{
    return d->includeEntities;
}

void AbstractStatusAction::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}
