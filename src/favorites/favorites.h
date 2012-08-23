#ifndef FAVORITES_H
#define FAVORITES_H

#include "../statuses/abstractstatusesmodel.h"

class Favorites : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString user_id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(Favorites)
public:
    explicit Favorites(QObject *parent = 0);

signals:
    void idChanged(const QString &userId);
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void countChanged(int count);
    void pageChanged(int page);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/favorites.json"); }
    void dataAdded(const QString &key, const QVariantMap &value);
    void dataChanged(const QString &key, const QVariantMap &value);
};

#endif // FAVORITES_H
