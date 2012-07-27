#ifndef MENTIONS_H
#define MENTIONS_H

#include "abstractstatusesmodel.h"

class Mentions : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool trim_user READ trimUser WRITE setTrimUser NOTIFY trimUserChanged)
    Q_PROPERTY(bool include_rts READ includeRts WRITE setIncludeRts NOTIFY includeRtsChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_PROPERTY(bool contributor_details READ contributorDetails WRITE setContributorDetails NOTIFY contributorDetailsChanged)
public:
    explicit Mentions(QObject *parent = 0);

signals:
    void countChanged(int count);
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void pageChanged(int page);
    void trimUserChanged(bool trimUser);
    void includeRtsChanged(bool includeRts);
    void includeEntitiesChanged(bool includeEntities);
    void contributorDetailsChanged(bool contributorDetails);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/statuses/mentions.json"); }
    void dataAdded(const QString &key, const QVariantMap &value);

private:
    Q_DISABLE_COPY(Mentions)
};

#endif // MENTIONS_H
