#ifndef SLUGS_H
#define SLUGS_H

#include "../tools/abstracttwittermodel.h"

class Slugs : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(QString lang READ lang WRITE setLang NOTIFY langChanged)
    Q_DISABLE_COPY(Slugs)
public:
    enum Roles {
        NameRole = Qt::UserRole + 1
        , SlugRole
        , SizeRole
    };
    explicit Slugs(QObject *parent = 0);
    ~Slugs();

    const QString &lang() const;
    void setLang(const QString &lang);

signals:
    void langChanged(const QString &lang);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("http://api.twitter.com/1/users/suggestions.json"); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // SLUGS_H
