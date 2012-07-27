#ifndef ABSTRACTUSERACTION_H
#define ABSTRACTUSERACTION_H

#include "../tools/abstracttwitteraction.h"

class AbstractUserAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractUserAction)
public:
    explicit AbstractUserAction(QObject *parent = 0);
    ~AbstractUserAction();

    const QString &userId() const;
    void setUserId(const QString &userId);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void includeEntitiesChanged(bool includeEntities);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTUSERACTION_H
