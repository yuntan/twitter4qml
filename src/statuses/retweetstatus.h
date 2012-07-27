#ifndef RETWEETSTATUS_H
#define RETWEETSTATUS_H

#include "abstractstatusaction.h"

class RetweetStatus : public AbstractStatusAction
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(bool trim_user READ trimUser WRITE setTrimUser NOTIFY trimUserChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(RetweetStatus)
public:
    explicit RetweetStatus(QObject *parent = 0);

signals:
    void idChanged(const QString &id);
    void trimUserChanged(bool trimUser);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/statuses/retweet/%1.json").arg(id())); }
};

#endif // RETWEETSTATUS_H
