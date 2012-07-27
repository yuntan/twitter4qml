#ifndef RETWEETS_H
#define RETWEETS_H

#include "abstractstatusesmodel.h"

class Retweets : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(QString status_id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(bool trim_user READ trimUser WRITE setTrimUser NOTIFY trimUserChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(Retweets)
public:
    explicit Retweets(QObject *parent = 0);

signals:
    void idChanged(const QString &id);
    void countChanged(int count);
    void trimUserChanged(bool trimUser);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/statuses/retweets/%1.json").arg(id())); }
};

#endif // RETWEETS_H
