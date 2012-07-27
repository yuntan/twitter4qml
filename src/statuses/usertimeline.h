#ifndef USERTIMELINE_H
#define USERTIMELINE_H

#include "abstractstatusesmodel.h"

class UserTimeline : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool trim_user READ trimUser WRITE setTrimUser NOTIFY trimUserChanged)
    Q_PROPERTY(bool include_rts READ includeRts WRITE setIncludeRts NOTIFY includeRtsChanged)
    Q_PROPERTY(bool exclude_replies READ excludeReplies WRITE setExcludeReplies NOTIFY excludeRepliesChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_PROPERTY(bool contributor_details READ contributorDetails WRITE setContributorDetails NOTIFY contributorDetailsChanged)
    Q_DISABLE_COPY(UserTimeline)
public:
    explicit UserTimeline(QObject *parent = 0);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void sinceIdChanged(const QString &sinceId);
    void countChanged(int count);
    void maxIdChanged(const QString &maxId);
    void pageChanged(int page);
    void trimUserChanged(bool trimUser);
    void includeRtsChanged(bool includeRts);
    void excludeRepliesChanged(bool excludeReplies);
    void includeEntitiesChanged(bool includeEntities);
    void contributorDetailsChanged(bool contributorDetails);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/statuses/user_timeline.json"); }
    void dataAdded(const QString &key, const QVariantMap &value);
};

#endif // USERTIMELINE_H
