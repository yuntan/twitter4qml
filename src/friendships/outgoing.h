#ifndef OUTGOING_H
#define OUTGOING_H

#include "abstractfriendshipidsmodel.h"

class Outgoing : public AbstractFriendshipIdsModel
{
    Q_OBJECT
    Q_PROPERTY(QString cursor READ cursor WRITE setCursor NOTIFY cursorChanged)
    Q_PROPERTY(bool stringifyIds READ stringifyIds WRITE setStringifyIds NOTIFY stringifyIdsChanged)
public:
    explicit Outgoing(QObject *parent = 0);

signals:
    void cursorChanged(const QString &cursor);
    void stringifyIdsChanged(bool stringifyIds);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/friendships/outgoing.json"); }
};

#endif // OUTGOING_H
