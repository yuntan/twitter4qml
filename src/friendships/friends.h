#ifndef FRIENDS_H
#define FRIENDS_H

#include "abstractfriendshipidsmodel.h"

class Friends : public AbstractFriendshipIdsModel
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(QString cursor READ cursor WRITE setCursor NOTIFY cursorChanged)
    Q_PROPERTY(bool stringify_ids READ stringifyIds WRITE setStringifyIds NOTIFY stringifyIdsChanged)
public:
    explicit Friends(QObject *parent = 0);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void cursorChanged(const QString &cursor);
    void stringifyIdsChanged(bool stringifyIds);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/friends/ids.json"); }
};

#endif // FRIENDS_H
