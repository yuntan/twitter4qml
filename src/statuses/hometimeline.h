#ifndef HOMETIMELINE_H
#define HOMETIMELINE_H

#include "abstractstatusesmodel.h"

class HomeTimeline : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool trim_user READ trimUser WRITE setTrimUser NOTIFY trimUserChanged)
    Q_PROPERTY(bool include_rts READ includeRts WRITE setIncludeRts NOTIFY includeRtsChanged)
    Q_PROPERTY(bool exclude_replies READ excludeReplies WRITE setExcludeReplies NOTIFY excludeRepliesChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_PROPERTY(bool contributor_details READ contributorDetails WRITE setContributorDetails NOTIFY contributorDetailsChanged)
    Q_DISABLE_COPY(HomeTimeline)
public:
    explicit HomeTimeline(QObject *parent = 0);

signals:
    void countChanged(int count);
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void pageChanged(int page);
    void trimUserChanged(bool trimUser);
    void includeRtsChanged(bool includeRts);
    void excludeRepliesChanged(bool excludeReplies);
    void includeEntitiesChanged(bool includeEntities);
    void contributorDetailsChanged(bool contributorDetails);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/statuses/home_timeline.json"); }
};

#endif // HOMETIMELINE_H
