#ifndef CREATEBLOCK_H
#define CREATEBLOCK_H

#include "abstractblockaction.h"

class CreateBlock : public AbstractBlockAction
{
    Q_OBJECT
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_PROPERTY(bool skip_status READ skipStatus WRITE setSkipStatus NOTIFY skipStatusChanged)
    Q_DISABLE_COPY(CreateBlock)
public:
    explicit CreateBlock(QObject *parent = 0);

signals:
    void includeEntitiesChanged(bool includeEntities);
    void skipStatusChanged(bool skipStatus);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/blocks/create.json"); }
};

#endif // CREATEBLOCK_H
