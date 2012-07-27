#ifndef DESTROYFRIENDSHIP_H
#define DESTROYFRIENDSHIP_H

#include "abstractfriendshipaction.h"

class DestroyFriendship : public AbstractFriendshipAction
{
    Q_OBJECT
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(DestroyFriendship)
public:
    explicit DestroyFriendship(QObject *parent = 0);

signals:
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/friendships/destroy.json"); }
};

#endif // DESTROYFRIENDSHIP_H
