#ifndef DAILY_H
#define DAILY_H

#include "../tools/abstracttwittermodel.h"

class Daily : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged DESIGNABLE false)
    Q_PROPERTY(bool exclude READ exclude WRITE setExclude NOTIFY excludeChanged)
    Q_DISABLE_COPY(Daily)
public:
    enum Roles {
        QueryRole = Qt::UserRole + 1
        , NameRole
        , PromotedContentRole
        , EventsRole
        , UrlRole
    };
    explicit Daily(QObject *parent = 0);
    ~Daily();

    const QString &date() const;
    void setDate(const QString &date);
    bool exclude() const;
    void setExclude(bool exclude);

public slots:
    void reload();

signals:
    void dateChanged(const QString &date);
    void excludeChanged(bool exclude);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("http://api.twitter.com/1/trends/daily.json"); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // DAILY_H
