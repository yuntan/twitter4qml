#ifndef DESTROYBLOCK_H
#define DESTROYBLOCK_H

#include "abstractblockaction.h"

class DestroyBlock : public AbstractBlockAction
{
    Q_OBJECT
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_PROPERTY(bool skip_status READ skipStatus WRITE setSkipStatus NOTIFY skipStatusChanged)
    Q_DISABLE_COPY(DestroyBlock)
public:
    explicit DestroyBlock(QObject *parent = 0);

signals:
    void includeEntitiesChanged(bool includeEntities);
    void skipStatusChanged(bool skipStatus);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/blocks/destroy.json"); }
};

#endif // DESTROYBLOCK_H
