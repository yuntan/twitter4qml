#ifndef LOOKUPUSERS_H
#define LOOKUPUSERS_H

#include "abstractusersmodel.h"

class LookupUsers : public AbstractUsersModel
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(LookupUsers)

public:
    explicit LookupUsers(QObject *parent = 0);

public slots:
    void reload();

signals:
    void idChanged(const QString &id);
    void screenNameChanged(const QString &screenName);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/users/lookup.json"); }
};

#endif // LOOKUPUSERS_H
