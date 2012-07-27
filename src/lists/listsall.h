#ifndef LISTSALL_H
#define LISTSALL_H

#include "abstractlistsmodel.h"

class ListsAll : public AbstractListsModel
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_DISABLE_COPY(ListsAll)
public:
    explicit ListsAll(QObject *parent = 0);
    
signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/all.json"); }
};

#endif // LISTSALL_H
