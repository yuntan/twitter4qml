#ifndef FRIENDSHIPS_H
#define FRIENDSHIPS_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

class UpdateFriendship;

class Friendships : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Friendships)
public:
    explicit Friendships(QObject *parent = 0);

    Q_INVOKABLE UpdateFriendship *update(QVariantMap parameters = QVariantMap());
};

#endif // FRIENDSHIPS_H
