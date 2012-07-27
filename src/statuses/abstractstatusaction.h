#ifndef ABSTRACTSTATUSACTION_H
#define ABSTRACTSTATUSACTION_H

#include "../tools/abstracttwitteraction.h"

class AbstractStatusAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractStatusAction)
public:
    explicit AbstractStatusAction(QObject *parent = 0);
    ~AbstractStatusAction();
    
    const QString &status() const;
    void setStatus(const QString &status);
    const QVariantList &media() const;
    void setMedia(const QVariantList &media);
    bool possiblySensitive() const;
    void setPossiblySensitive(bool possiblySensitive);
    const QString &inReplyToStatusId() const;
    void setInReplyToStatusId(const QString &inReplyToStatusId);
    double latitude() const;
    void setLatitude(double latitude);
    double longitude() const;
    void setLongitude(double longitude);
    const QString &placeId() const;
    void setPlaceId(const QString &placeId);
    const QString &displayCoordinates() const;
    void setDisplayCoordinates(const QString &displayCoordinates);
    const QString &id() const;
    void setId(const QString &id);
    bool trimUser() const;
    void setTrimUser(bool trimUser);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);

signals:
    void statusChanged(const QString &status);
    void mediaChanged(const QVariantList &media);
    void possiblySensitiveChanged(bool possiblySensitive);
    void inReplyToStatusIdChanged(const QString &inReplyToStatusId);
    void latitudeChanged(double latitude);
    void longitudeChanged(double longitude);
    void placeIdChanged(const QString &placeId);
    void displayCoordinatesChanged(const QString &displayCoordinates);
    void idChanged(const QString &id);
    void trimUserChanged(bool trimUser);
    void includeEntitiesChanged(bool includeEntities);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTSTATUSACTION_H
