#ifndef AVAILABLE_H
#define AVAILABLE_H

#include "../tools/abstracttwittermodel.h"

class Available : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(double _lat READ latitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double _long READ longitude WRITE setLongitude NOTIFY longitudeChanged)
    Q_DISABLE_COPY(Available)
public:
    enum Roles {
        CountryRole = Qt::UserRole + 1
        , CountryCodeRole
        , NameRole
        , ParentIdRole
        , PlaceTypeRole
        , UrlRole
        , WoeidRole
    };
    explicit Available(QObject *parent = 0);
    ~Available();

    double latitude() const;
    void setLatitude(double latitude);
    double longitude() const;
    void setLongitude(double longitude);

public slots:
    void reload();

signals:
    void latitudeChanged(double latitude);
    void longitudeChanged(double longitude);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("http://api.twitter.com/1/trends/available.json"); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // AVAILABLE_H
