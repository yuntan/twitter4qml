#ifndef BLOCKINGIDS_H
#define BLOCKINGIDS_H

#include "../statuses/abstractidsmodel.h"

class BlockingIds : public AbstractIdsModel
{
    Q_OBJECT
    Q_PROPERTY(bool stringifyIds READ stringifyIds WRITE setStringifyIds NOTIFY stringifyIdsChanged)
    Q_DISABLE_COPY(BlockingIds)
public:
    explicit BlockingIds(QObject *parent = 0);

signals:
    void stringifyIdsChanged(bool stringifyIds);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/statuses/%1/blocking/ids.json").arg(id())); }
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
};

#endif // BLOCKINGIDS_H
