#ifndef SUBSCRIBELIST_H
#define SUBSCRIBELIST_H

#include "abstractlistaction.h"

class SubscribeList : public AbstractListAction
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ listId WRITE setListId NOTIFY listIdChanged)
    Q_DISABLE_COPY(SubscribeList)
public:
    explicit SubscribeList(QObject *parent = 0);

signals:
    void listIdChanged(const QString &listId);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/subscribers/create.json"); }
};

#endif // SUBSCRIBELIST_H
