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

#ifndef UPDATESTATUS_H
#define UPDATESTATUS_H

#include "abstractstatusaction.h"

class UpdateStatus : public AbstractStatusAction
{
    Q_OBJECT
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString in_reply_to_status_id READ inReplyToStatusId WRITE setInReplyToStatusId NOTIFY inReplyToStatusIdChanged)
    Q_PROPERTY(double _lat READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double _long READ longitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(QString place_id READ placeId WRITE setPlaceId NOTIFY placeIdChanged)
    Q_PROPERTY(QString display_coordinates READ displayCoordinates WRITE setDisplayCoordinates NOTIFY displayCoordinatesChanged)
    Q_PROPERTY(bool trim_user READ trimUser WRITE setTrimUser NOTIFY trimUserChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)

    Q_DISABLE_COPY(UpdateStatus)
public:
    explicit UpdateStatus(QObject *parent = 0);
    
signals:
    void statusChanged(const QString &status);
    void inReplyToStatusIdChanged(const QString &inReplyToStatusId);
    void latitudeChanged(double latitude);
    void longitudeChanged(double longitude);
    void placeIdChanged(const QString &placeId);
    void displayCoordinatesChanged(const QString &displayCoordinates);
    void trimUserChanged(bool trimUser);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/statuses/update.json"); }
};

#endif // UPDATESTATUS_H
