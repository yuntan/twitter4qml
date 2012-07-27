#ifndef ABSTRACTLISTSMODEL_H
#define ABSTRACTLISTSMODEL_H

#include "../tools/abstracttwittermodel.h"

class AbstractListsModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractListsModel)

public:
    enum Roles {
        CreatedAtRole = Qt::UserRole + 1
        , DescriptionRole
        , FollowingRole
        , FullNameRole
        , IdRole
        , IdStrRole
        , MemberCountRole
        , ModeRole
        , NameRole
        , SlugRole
        , SubscriberCountRole
        , UriRole
        , UserRole
    };

    explicit AbstractListsModel(QObject *parent = 0);
    ~AbstractListsModel();

    const QString &userId() const;
    void setUserId(const QString &userId);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    int count() const;
    void setCount(int count);
    const QString &cursor() const;
    void setCursor(const QString &cursor);

    int nextCursor() const;
    void setNextCursor(int nextCursor);
    const QString &nextCursorStr() const;
    void setNextCursorStr(const QString &nextCursorStr);
    int previousCursor() const;
    void setPreviousCursor(int previousCursor);
    const QString &previousCursorStr() const;
    void setPreviousCursorStr(const QString &previousCursorStr);

    DataManager::DataType dataType() const { return DataManager::ListData; }

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
    AuthorizeBy authenticationMethod() const;
    QString httpMethod() const;
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTLISTSMODEL_H
