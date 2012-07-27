#ifndef ABSTRACTBLOCKACTION_H
#define ABSTRACTBLOCKACTION_H

#include "../tools/abstracttwitteraction.h"

class AbstractBlockAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_DISABLE_COPY(AbstractBlockAction)
public:
    explicit AbstractBlockAction(QObject *parent = 0);
    ~AbstractBlockAction();

    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    const QString &userId() const;
    void setUserId(const QString &userId);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);
    bool skipStatus() const;
    void setSkipStatus(bool skipStatus);

signals:
    void screenNameChanged(const QString &screenName);
    void userIdChanged(const QString &userId);
    void includeEntitiesChanged(bool includeEntities);
    void skipStatusChanged(bool skipStatus);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTBLOCKACTION_H
