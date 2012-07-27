#ifndef GEOSEARCH_H
#define GEOSEARCH_H

#include "../tools/abstracttwittermodel.h"

class GeoSearch : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(double _lat READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double _long READ longitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_PROPERTY(QString query READ query WRITE setQuery NOTIFY queryChanged)
    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(QString granularity READ granularity WRITE setGranularity NOTIFY granularityChanged)
    Q_PROPERTY(QString accuracy READ accuracy WRITE setAccuracy NOTIFY accuracyChanged)
    Q_PROPERTY(int max_results READ maxResults WRITE setMaxResults NOTIFY maxResultsChanged)
    Q_PROPERTY(QString contained_within READ containedWithin WRITE setContainedWithin NOTIFY containedWithinChanged)
    Q_DISABLE_COPY(GeoSearch)
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
    explicit GeoSearch(QObject *parent = 0);
    ~GeoSearch();

    double latitude() const;
    void setLatitude(double latitude);
    double longitude() const;
    void setLongitude(double longitude);
    const QString &query() const;
    void setQuery(const QString &query);
    const QString &ip() const;
    void setIp(const QString &ip);
    const QString &granularity() const;
    void setGranularity(const QString &granularity);
    const QString &accuracy() const;
    void setAccuracy(const QString &accuracy);
    int maxResults() const;
    void setMaxResults(int maxResults);
    const QString &containedWithin() const;
    void setContainedWithin(const QString &containedWithin);

public slots:
    void reload();

signals:
    void latitudeChanged(double latitude);
    void longitudeChanged(double longitude);
    void queryChanged(const QString &query);
    void ipChanged(const QString &ip);
    void granularityChanged(const QString &granularity);
    void accuracyChanged(const QString &accuracy);
    void maxResultsChanged(int maxResults);
    void containedWithinChanged(const QString &containedWithin);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("http://api.twitter.com/1/geo/search.json"); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // GEOSEARCH_H
