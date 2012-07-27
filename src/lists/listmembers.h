#ifndef LISTMEMBERS_H
#define LISTMEMBERS_H

#include "../users/abstractusersmodel.h"

class ListMembers : public AbstractUsersModel
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString slug READ slug WRITE setSlug NOTIFY slugChanged)
    Q_PROPERTY(QString owner_screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(QString cursor READ cursor WRITE setCursor NOTIFY cursorChanged)

    Q_PROPERTY(int next_cursor READ nextCursor NOTIFY nextCursorChanged DESIGNABLE false)
    Q_PROPERTY(QString next_cursor_str READ nextCursorStr NOTIFY nextCursorStrChanged DESIGNABLE false)
    Q_PROPERTY(int previous_cursor READ previousCursor NOTIFY previousCursorChanged DESIGNABLE false)
    Q_PROPERTY(QString previous_cursor_str READ previousCursorStr NOTIFY previousCursorStrChanged DESIGNABLE false)
    Q_DISABLE_COPY(ListMembers)

public:
    explicit ListMembers(QObject *parent = 0);
    ~ListMembers();

    const QString &slug() const;
    void setSlug(const QString &slug);

public slots:
    void reload();

signals:
    void idChanged(const QString &id);
    void screenNameChanged(const QString &screenName);
    void includeEntitiesChanged(bool includeEntities);
    void cursorChanged(const QString &cursor);
    void slugChanged(const QString &slug);

    void nextCursorChanged(int nextCursor) const;
    void nextCursorStrChanged(const QString &nextCursorStr) const;
    void previousCursorChanged(int previousCursor) const;
    void previousCursorStrChanged(const QString &previousCursorStr) const;

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/members.json"); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // LISTMEMBERS_H
