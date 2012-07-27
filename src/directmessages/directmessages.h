#ifndef DIRECTMESSAGES_H
#define DIRECTMESSAGES_H

#include "abstractdirectmessagesmodel.h"

class DirectMessages : public AbstractDirectMessagesModel
{
    Q_OBJECT
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)

    Q_DISABLE_COPY(DirectMessages)
public:
    explicit DirectMessages(QObject *parent = 0);

signals:
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void countChanged(int count);
    void pageChanged(int page);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/direct_messages.json"); }
    void dataAdded(const QString &key, const QVariantMap &value);
};

#endif // DIRECTMESSAGES_H
