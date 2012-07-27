#ifndef SHOWUSER_H
#define SHOWUSER_H

#include "abstractuseraction.h"

class ShowUser : public AbstractUserAction
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(ShowUser)
public:
    explicit ShowUser(QObject *parent = 0);

public slots:
    void exec();

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(bool screenName);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/users/show.json"); }
    QString httpMethod() const { return "GET"; }
};

#endif // SHOWUSER_H
