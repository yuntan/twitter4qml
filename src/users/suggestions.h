#ifndef SUGGESTIONS_H
#define SUGGESTIONS_H

#include "abstractusersmodel.h"

class Suggestions : public AbstractUsersModel
{
    Q_OBJECT
    Q_PROPERTY(QString slug READ slug WRITE setSlug NOTIFY slugChanged)
    Q_PROPERTY(QString lang READ lang WRITE setLang NOTIFY langChanged)
    Q_DISABLE_COPY(Suggestions)
public:
    explicit Suggestions(QObject *parent = 0);
    ~Suggestions();

    const QString &slug() const;
    void setSlug(const QString &slug);
    const QString &lang() const;
    void setLang(const QString &lang);

signals:
    void slugChanged(const QString &slug);
    void langChanged(const QString &lang);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/users/suggestions/%1.json").arg(slug())); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // SUGGESTIONS_H
