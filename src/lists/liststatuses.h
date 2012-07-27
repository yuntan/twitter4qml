#ifndef LISTSTATUSES_H
#define LISTSTATUSES_H

#include "../statuses/abstractstatusesmodel.h"

class ListStatuses : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ listId WRITE setListId NOTIFY listIdChanged)
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int per_page READ perPage WRITE setPerPage NOTIFY perPageChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool include_rts READ includeRts WRITE setIncludeRts NOTIFY includeRtsChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(ListStatuses)
public:
    explicit ListStatuses(QObject *parent = 0);

signals:
    void listIdChanged(const QString &listId);
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void pageChanged(int page);
    void perPageChanged(int perPage);
    void includeRtsChanged(bool includeRts);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/statuses.json"); }
};

#endif // LISTSTATUSES_H
