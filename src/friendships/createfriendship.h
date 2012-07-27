#ifndef CREATEFRIENDSHIP_H
#define CREATEFRIENDSHIP_H

#include "abstractfriendshipaction.h"

class CreateFriendship : public AbstractFriendshipAction
{
    Q_OBJECT
    Q_PROPERTY(bool follow READ follow WRITE setFollow NOTIFY followChanged)
    Q_DISABLE_COPY(CreateFriendship)
public:
    explicit CreateFriendship(QObject *parent = 0);

signals:
    void followChanged(bool follow);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/friendships/create.json"); }
};

#endif // CREATEFRIENDSHIP_H
