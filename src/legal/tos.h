#ifndef TOS_H
#define TOS_H

#include "../tools/abstracttwitteraction.h"

class Tos : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString tos READ tos WRITE setTos NOTIFY tosChanged DESIGNABLE false USER true)
    Q_DISABLE_COPY(Tos)
public:
    explicit Tos(QObject *parent = 0);
    ~Tos();

    const QString &tos() const;
    void setTos(const QString &tos);

signals:
    void tosChanged(const QString &tos);
    void skipStatusChanged(bool skipStatus);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/legal/tos.json"); }
    virtual AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }

private:
    class Private;
    Private *d;
};

#endif // TOS_H
