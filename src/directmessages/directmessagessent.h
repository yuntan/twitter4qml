#ifndef DIRECTMESSAGESSENT_H
#define DIRECTMESSAGESSENT_H

#include "abstractdirectmessagesmodel.h"

class DirectMessagesSent : public AbstractDirectMessagesModel
{
    Q_OBJECT
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(DirectMessagesSent)
public:
    explicit DirectMessagesSent(QObject *parent = 0);

signals:
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void countChanged(int count);
    void pageChanged(int page);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/direct_messages/sent.json"); }
    void dataAdded(const QString &key, const QVariantMap &value);
};

#endif // DIRECTMESSAGESSENT_H
