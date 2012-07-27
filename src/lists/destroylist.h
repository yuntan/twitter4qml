#ifndef DESTROYLIST_H
#define DESTROYLIST_H

#include "abstractlistaction.h"

class DestroyList : public AbstractListAction
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ listId WRITE setListId NOTIFY listIdChanged)
    Q_DISABLE_COPY(DestroyList)
public:
    explicit DestroyList(QObject *parent = 0);

signals:
    void listIdChanged(const QString &listId);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/destroy.json"); }
};

#endif // DESTROYLIST_H
