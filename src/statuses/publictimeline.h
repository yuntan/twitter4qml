#ifndef PUBLICTIMELINE_H
#define PUBLICTIMELINE_H

#include "abstractstatusesmodel.h"

class PublicTimeline : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(bool trim_user READ trimUser WRITE setTrimUser NOTIFY trimUserChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(PublicTimeline)
public:
    explicit PublicTimeline(QObject *parent = 0);

signals:
    void trimUserChanged(bool trimUser);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/statuses/public_timeline.json"); }
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
};

#endif // PUBLICTIMELINE_H
