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

#ifndef STATUSESUPDATE_H
#define STATUSESUPDATE_H

#include "abstractstatusaction.h"

class TWITTER4QML_EXPORT StatusesUpdate : public AbstractStatusAction
{
    Q_OBJECT
    Q_PROPERTY(QString status READ status WRITE status NOTIFY statusChanged)
    Q_PROPERTY(QString in_reply_to_status_id READ in_reply_to_status_id WRITE in_reply_to_status_id NOTIFY in_reply_to_status_idChanged)
    Q_PROPERTY(double _lat READ latitude WRITE latitude NOTIFY latitudeChanged)
    Q_PROPERTY(double _long READ longitude WRITE longitude NOTIFY longitudeChanged)
    Q_PROPERTY(QString place_id READ place_id WRITE place_id NOTIFY place_idChanged)
    Q_PROPERTY(QString display_coordinates READ display_coordinates WRITE display_coordinates NOTIFY display_coordinatesChanged)
    Q_PROPERTY(bool trim_user READ trim_user WRITE trim_user NOTIFY trim_userChanged)
//    Q_PROPERTY(bool include_entities READ include_entities WRITE include_entities NOTIFY include_entitiesChanged)

    Q_DISABLE_COPY(StatusesUpdate)
public:
    explicit StatusesUpdate(QObject *parent = 0);
    
signals:
    void statusChanged(const QString &status);
    void in_reply_to_status_idChanged(const QString &in_reply_to_status_id);
    void latitudeChanged(double latitude);
    void longitudeChanged(double longitude);
    void place_idChanged(const QString &place_id);
    void display_coordinatesChanged(const QString &display_coordinates);
    void trim_userChanged(bool trim_user);
//    void include_entitiesChanged(bool include_entities);

protected:
    virtual AuthorizeBy authenticationMethod() const { return AuthorizeByHeader; }
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/statuses/update.json"); }

    ADD_PROPERTY(const QString &, status, QString)
    ADD_PROPERTY(const QString &, in_reply_to_status_id, QString)
    ADD_PROPERTY(double, latitude, double)
    ADD_PROPERTY(double, longitude, double)
    ADD_PROPERTY(const QString &, place_id, QString)
    ADD_PROPERTY(const QString &, display_coordinates, QString)
};

#endif // STATUSESUPDATE_H
