#ifndef ABSTRACTFRIENDSHIPACTION_H
#define ABSTRACTFRIENDSHIPACTION_H

#include "../tools/abstracttwitteraction.h"

class AbstractFriendshipAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_DISABLE_COPY(AbstractFriendshipAction)
public:
    explicit AbstractFriendshipAction(QObject *parent = 0);
    ~AbstractFriendshipAction();

    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    const QString &userId() const;
    void setUserId(const QString &userId);
    bool follow() const;
    void setFollow(bool follow);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);

signals:
    void screenNameChanged(const QString &screenName);
    void userIdChanged(const QString &userId);
    void followChanged(bool follow);
    void includeEntitiesChanged(bool includeEntities);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTFRIENDSHIPACTION_H
