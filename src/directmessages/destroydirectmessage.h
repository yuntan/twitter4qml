#ifndef DESTROYDIRECTMESSAGE_H
#define DESTROYDIRECTMESSAGE_H

#include "abstractdirectmessageaction.h"

class DestroyDirectMessage : public AbstractDirectMessageAction
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(DestroyDirectMessage)
public:
    explicit DestroyDirectMessage(QObject *parent = 0);

signals:
    void idChanged(const QString &id);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/direct_messages/destroy/%1.json").arg(id())); }
};

#endif // DESTROYDIRECTMESSAGE_H
