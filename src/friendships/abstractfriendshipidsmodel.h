#ifndef ABSTRACTFRIENDSHIPIDSMODEL_H
#define ABSTRACTFRIENDSHIPIDSMODEL_H

#include "../tools/abstracttwittermodel.h"

class AbstractFriendshipIdsModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(int next_cursor READ nextCursor NOTIFY nextCursorChanged DESIGNABLE false)
    Q_PROPERTY(QString next_cursor_str READ nextCursorStr NOTIFY nextCursorStrChanged DESIGNABLE false)
    Q_PROPERTY(int previous_cursor READ previousCursor NOTIFY previousCursorChanged DESIGNABLE false)
    Q_PROPERTY(QString previous_cursor_str READ previousCursorStr NOTIFY previousCursorStrChanged DESIGNABLE false)
    Q_DISABLE_COPY(AbstractFriendshipIdsModel)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1
        , IdStrRole
    };
    explicit AbstractFriendshipIdsModel(QObject *parent = 0);
    ~AbstractFriendshipIdsModel();

    const QString &userId() const;
    void setUserId(const QString &userId);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    const QString &cursor() const;
    void setCursor(const QString &cursor);
    bool stringifyIds() const;
    void setStringifyIds(bool stringifyIds);

    int nextCursor() const;
    void setNextCursor(int nextCursor);
    const QString &nextCursorStr() const;
    void setNextCursorStr(const QString &nextCursorStr);
    int previousCursor() const;
    void setPreviousCursor(int previousCursor);
    const QString &previousCursorStr() const;
    void setPreviousCursorStr(const QString &previousCursorStr);

public slots:
    virtual void reload();

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void cursorChanged(const QString &cursor);
    void stringifyIdsChanged(bool stringifyIds);

    void nextCursorChanged(int nextCursor) const;
    void nextCursorStrChanged(const QString &nextCursorStr) const;
    void previousCursorChanged(int previousCursor) const;
    void previousCursorStrChanged(const QString &previousCursorStr) const;

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTFRIENDSHIPIDSMODEL_H
