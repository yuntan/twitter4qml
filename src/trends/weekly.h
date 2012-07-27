#ifndef WEEKLY_H
#define WEEKLY_H

#include "../tools/abstracttwittermodel.h"

class Weekly : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged DESIGNABLE false)
    Q_PROPERTY(bool exclude READ exclude WRITE setExclude NOTIFY excludeChanged)
    Q_DISABLE_COPY(Weekly)
public:
    enum Roles {
        QueryRole = Qt::UserRole + 1
        , NameRole
        , PromotedContentRole
        , EventsRole
        , UrlRole
    };
    explicit Weekly(QObject *parent = 0);
    ~Weekly();

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
    QUrl api() const { return QUrl("http://api.twitter.com/1/trends/weekly.json"); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // WEEKLY_H
