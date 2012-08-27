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
