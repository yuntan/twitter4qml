#ifndef TRENDS_H
#define TRENDS_H

#include "../tools/abstracttwittermodel.h"

class Trends : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(int woeid READ woeid WRITE setWoeid NOTIFY woeidChanged DESIGNABLE false)
    Q_PROPERTY(bool exclude READ exclude WRITE setExclude NOTIFY excludeChanged)
    Q_DISABLE_COPY(Trends)
public:
    enum Roles {
        QueryRole = Qt::UserRole + 1
        , NameRole
        , PromotedContentRole
        , EventsRole
        , UrlRole
    };
    explicit Trends(QObject *parent = 0);
    ~Trends();

    int woeid() const;
    void setWoeid(int woeid);
    bool exclude() const;
    void setExclude(bool exclude);

public slots:
    void reload();

signals:
    void woeidChanged(int woeid);
    void excludeChanged(bool exclude);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/trends/%1.json").arg(woeid())); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // TRENDS_H
