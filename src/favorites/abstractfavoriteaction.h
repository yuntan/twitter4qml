#ifndef ABSTRACTFAVORITEACTION_H
#define ABSTRACTFAVORITEACTION_H

#include "../statuses/abstractstatusaction.h"

class AbstractFavoriteAction : public AbstractStatusAction
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(AbstractFavoriteAction)
public:
    explicit AbstractFavoriteAction(QObject *parent = 0);

signals:
    void idChanged(const QString &id);
    void includeEntitiesChanged(bool includeEntities);
};

#endif // ABSTRACTFAVORITEACTION_H
