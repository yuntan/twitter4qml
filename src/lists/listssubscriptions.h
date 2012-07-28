#ifndef LISTSSUBSCRIPTIONS_H
#define LISTSSUBSCRIPTIONS_H

#include "abstractlistsmodel.h"

class ListsSubscriptions : public AbstractListsModel
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(QString cursor READ cursor WRITE setCursor NOTIFY cursorChanged)

    Q_PROPERTY(int next_cursor READ nextCursor NOTIFY nextCursorChanged DESIGNABLE false)
    Q_PROPERTY(QString next_cursor_str READ nextCursorStr NOTIFY nextCursorStrChanged DESIGNABLE false)
    Q_PROPERTY(int previous_cursor READ previousCursor NOTIFY previousCursorChanged DESIGNABLE false)
    Q_PROPERTY(QString previous_cursor_str READ previousCursorStr NOTIFY previousCursorStrChanged DESIGNABLE false)
    Q_DISABLE_COPY(ListsSubscriptions)
public:
    ListsSubscriptions(QObject *parent = 0);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void countChanged(int count);
    void cursorChanged(const QString &cursor);

    void nextCursorChanged(int nextCursor) const;
    void nextCursorStrChanged(const QString &nextCursorStr) const;
    void previousCursorChanged(int previousCursor) const;
    void previousCursorStrChanged(const QString &previousCursorStr) const;

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/subscriptions.json"); }
    void parseDone(const QVariant &result);
};

#endif // LISTSSUBSCRIPTIONS_H