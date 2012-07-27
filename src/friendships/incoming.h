#ifndef INCOMING_H
#define INCOMING_H

#include "abstractfriendshipidsmodel.h"

class Incoming : public AbstractFriendshipIdsModel
{
    Q_OBJECT
    Q_PROPERTY(QString cursor READ cursor WRITE setCursor NOTIFY cursorChanged)
    Q_PROPERTY(bool stringifyIds READ stringifyIds WRITE setStringifyIds NOTIFY stringifyIdsChanged)
public:
    explicit Incoming(QObject *parent = 0);

signals:
    void cursorChanged(const QString &cursor);
    void stringifyIdsChanged(bool stringifyIds);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/friendships/incoming.json"); }
};

#endif // INCOMING_H
