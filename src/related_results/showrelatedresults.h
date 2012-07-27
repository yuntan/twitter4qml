#ifndef SHOWRELATEDRESULTS_H
#define SHOWRELATEDRESULTS_H

#include "../statuses/abstractstatusesmodel.h"

class ShowRelatedResults : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
public:
    explicit ShowRelatedResults(QObject *parent = 0);

signals:
    void idChanged(const QString &id);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/related_results/show/%1.json").arg(id())); }
    void parseDone(const QVariant &result);

private:
    Q_DISABLE_COPY(ShowRelatedResults)
};

#endif // SHOWRELATEDRESULTS_H
