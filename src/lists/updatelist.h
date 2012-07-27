#ifndef UPDATELIST_H
#define UPDATELIST_H

#include "abstractlistaction.h"

class UpdateList : public AbstractListAction
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ listId WRITE setListId NOTIFY listIdChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_DISABLE_COPY(UpdateList)
public:
    explicit UpdateList(QObject *parent = 0);

signals:
    void listIdChanged(const QString &listId);
    void descriptionChanged(const QString &description);
    void modeChanged(const QString &mode);
    void nameChanged(const QString &name);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/update.json"); }
};

#endif // UPDATELIST_H
