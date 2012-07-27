#ifndef PRIVACY_H
#define PRIVACY_H

#include "../tools/abstracttwitteraction.h"

class Privacy : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString privacy READ privacy WRITE setPrivacy NOTIFY privacyChanged DESIGNABLE false USER true)
    Q_DISABLE_COPY(Privacy)
public:
    explicit Privacy(QObject *parent = 0);
    ~Privacy();

    const QString &privacy() const;
    void setPrivacy(const QString &privacy);

signals:
    void privacyChanged(const QString &privacy);
    void skipStatusChanged(bool skipStatus);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/legal/privacy.json"); }
    virtual AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }

private:
    class Private;
    Private *d;
};

#endif // PRIVACY_H
