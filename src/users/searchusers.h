#ifndef SEARCHUSERS_H
#define SEARCHUSERS_H

#include "abstractusersmodel.h"

class SearchUsers : public AbstractUsersModel
{
    Q_OBJECT
    Q_PROPERTY(QString q READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(int per_page READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(SearchUsers)

public:
    explicit SearchUsers(QObject *parent = 0);

public slots:
    void reload();

signals:
    void idChanged(const QString &id);
    void pageChanged(int page);
    void countChanged(int count);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/users/search.json"); }
};

#endif // SEARCHUSERS_H
