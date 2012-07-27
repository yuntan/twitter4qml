#include "friendships.h"
#include "updatefriendship.h"

#include <QtDeclarative/qdeclarative.h>

Friendships::Friendships(QObject *parent)
    : QObject(parent)
{
    qmlRegisterUncreatableType<UpdateFriendship>("Twitter4QML", 1, 0, "UpdateFriendship", "use twitter4qml.friendships.update()");
}

UpdateFriendship *Friendships::update(QVariantMap parameters)
{
    return new UpdateFriendship(parameters);
}
