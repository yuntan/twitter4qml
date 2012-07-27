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
