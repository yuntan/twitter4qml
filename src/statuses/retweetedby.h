#ifndef RETWEETEDBY_H
#define RETWEETEDBY_H

#include "../users/abstractusersmodel.h"

class RetweetedBy : public AbstractUsersModel
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_DISABLE_COPY(RetweetedBy)
public:
    explicit RetweetedBy(QObject *parent = 0);

signals:
    void idChanged(const QString &id);
    void countChanged(int count);
    void pageChanged(int page);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/statuses/%1/retweeted_by.json").arg(id())); }
};

#endif // RETWEETEDBY_H
