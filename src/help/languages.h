#ifndef LANGUAGES_H
#define LANGUAGES_H

#include "../tools/abstracttwittermodel.h"

class Languages : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(Languages)
public:
    enum Roles {
        CodeRole = Qt::UserRole + 1
        , NameRole
        , StatusRole
    };
    explicit Languages(QObject *parent = 0);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("http://api.twitter.com/1/help/languages.json"); }
    void parseDone(const QVariant &result);
};

#endif // LANGUAGES_H
