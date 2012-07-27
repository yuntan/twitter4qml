#ifndef UNSUBSCRIBELIST_H
#define UNSUBSCRIBELIST_H

#include "abstractlistaction.h"

class UnsubscribeList : public AbstractListAction
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ listId WRITE setListId NOTIFY listIdChanged)
    Q_DISABLE_COPY(UnsubscribeList)
public:
    explicit UnsubscribeList(QObject *parent = 0);

signals:
    void listIdChanged(const QString &listId);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/subscribers/destroy.json"); }
};

#endif // UNSUBSCRIBELIST_H
