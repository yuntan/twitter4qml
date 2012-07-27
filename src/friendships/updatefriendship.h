#ifndef UPDATEFRIENDSHIP_H
#define UPDATEFRIENDSHIP_H

#include "../tools/abstracttwitteraction.h"

class UpdateFriendship : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(bool device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(bool retweets READ retweets WRITE setRetweets NOTIFY retweetsChanged)
public:
    explicit UpdateFriendship(QVariantMap parameters, QObject *parent = 0);
    ~UpdateFriendship();

    const QString &userId() const;
    void setUserId(const QString &userId);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    bool device() const;
    void setDevice(bool device);
    bool retweets() const;
    void setRetweets(bool retweets);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void deviceChanged(bool device);
    void retweetsChanged(bool retweets);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/friendships/update.json"); }
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "POST"; }

private:
    class Private;
    Private *d;
};

#endif // UPDATEFRIENDSHIP_H
