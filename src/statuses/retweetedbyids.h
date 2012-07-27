#ifndef RETWEETEDBYIDS_H
#define RETWEETEDBYIDS_H

#include "abstractidsmodel.h"

class RetweetedByIds : public AbstractIdsModel
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_DISABLE_COPY(RetweetedByIds)
public:
    explicit RetweetedByIds(QObject *parent = 0);

signals:
    void idChanged(const QString &id);
    void countChanged(int count);
    void pageChanged(int page);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/statuses/%1/retweeted_by/ids.json").arg(id())); }
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
};

#endif // RETWEETEDBYIDS_H
