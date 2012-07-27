#ifndef BLOCKEXISTS_H
#define BLOCKEXISTS_H

#include "abstractblockaction.h"

class BlockExists : public AbstractBlockAction
{
    Q_OBJECT
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_PROPERTY(bool skip_status READ skipStatus WRITE setSkipStatus NOTIFY skipStatusChanged)
    Q_DISABLE_COPY(BlockExists)
public:
    explicit BlockExists(QObject *parent = 0);

signals:
    void includeEntitiesChanged(bool includeEntities);
    void skipStatusChanged(bool skipStatus);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/blocks/exists.json"); }
    QString httpMethod() const { return "GET"; }
};

#endif // BLOCKEXISTS_H
