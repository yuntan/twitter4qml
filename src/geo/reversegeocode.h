#ifndef REVERSEGEOCODE_H
#define REVERSEGEOCODE_H

#include "../tools/abstracttwittermodel.h"

class ReverseGeocode : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(double _lat READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double _long READ longitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(QString granularity READ granularity WRITE setGranularity NOTIFY granularityChanged)
    Q_PROPERTY(QString accuracy READ accuracy WRITE setAccuracy NOTIFY accuracyChanged)
    Q_PROPERTY(int max_results READ maxResults WRITE setMaxResults NOTIFY maxResultsChanged)
    Q_DISABLE_COPY(ReverseGeocode)
public:
    enum Roles {
        AttrubutesRole = Qt::UserRole + 1
        , BoundingBoxRole
        , ContainedWithinRole
        , CountryRole
        , CountryCodeRole
        , FullNameRole
        , IdRole
        , IdStrRole
        , NameRole
        , PlaceTypeRole
        , UrlRole
    };
    explicit ReverseGeocode(QObject *parent = 0);
    ~ReverseGeocode();

    double latitude() const;
    void setLatitude(double latitude);
    double longitude() const;
    void setLongitude(double longitude);
    const QString &granularity() const;
    void setGranularity(const QString &granularity);
    const QString &accuracy() const;
    void setAccuracy(const QString &accuracy);
    int maxResults() const;
    void setMaxResults(int maxResults);

public slots:
    void reload();

signals:
    void latitudeChanged(double latitude);
    void longitudeChanged(double longitude);
    void granularityChanged(const QString &granularity);
    void accuracyChanged(const QString &accuracy);
    void maxResultsChanged(int maxResults);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("http://api.twitter.com/1/geo/reverse_geocode.json"); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // REVERSEGEOCODE_H
