#include "abstractlistsmodel.h"

class AbstractListsModel::Private
{
public:
    Private();

    QString userId;
    QString screenName;
    int count;
    QString cursor;

    int nextCursor;
    QString nextCursorStr;
    int previousCursor;
    QString previousCursorStr;
};

AbstractListsModel::Private::Private()
    : count(0)
    , nextCursor(0)
    , previousCursor(0)
{
}

AbstractListsModel::AbstractListsModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[CreatedAtRole] = "created_at";
    roles[DescriptionRole] = "description";
    roles[FollowingRole] = "following";
    roles[FullNameRole] = "full_name";
    roles[IdRole] = "id";
    roles[IdStrRole] = "id_str";
    roles[MemberCountRole] = "member_count";
    roles[ModeRole] = "mode";
    roles[NameRole] = "name";
    roles[SlugRole] = "slug";
    roles[SubscriberCountRole] = "subscriber_count";
    roles[UriRole] = "uri";
    roles[UserRole] = "user";
    setRoleNames(roles);
}

AbstractListsModel::~AbstractListsModel()
{
    delete d;
}

AbstractTwitterModel::AuthorizeBy AbstractListsModel::authenticationMethod() const
{
    return AuthorizeByUrl;
}

QString AbstractListsModel::httpMethod() const
{
    return "GET";
}

void AbstractListsModel::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                addData(result.toMap());
            }
        }
    } else {
        DEBUG() << result.type() << result;
    }
}

const QString &AbstractListsModel::userId() const
{
    return d->userId;
}

void AbstractListsModel::setUserId(const QString &userId)
{
    if (d->userId == userId) return;
    d->userId = userId;
    emit userIdChanged(userId);
}

const QString &AbstractListsModel::screenName() const
{
    return d->screenName;
}

void AbstractListsModel::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

int AbstractListsModel::count() const
{
    return d->count;
}

void AbstractListsModel::setCount(int count)
{
    if (d->count == count) return;
    d->count = count;
    emit countChanged(count);
}

const QString &AbstractListsModel::cursor() const
{
    return d->cursor;
}

void AbstractListsModel::setCursor(const QString &cursor)
{
    if (d->cursor == cursor) return;
    d->cursor = cursor;
    emit cursorChanged(cursor);
}

int AbstractListsModel::nextCursor() const
{
    return d->nextCursor;
}

void AbstractListsModel::setNextCursor(int nextCursor)
{
    if (d->nextCursor == nextCursor) return;
    d->nextCursor = nextCursor;
    emit nextCursorChanged(nextCursor);
}

const QString &AbstractListsModel::nextCursorStr() const
{
    return d->nextCursorStr;
}

void AbstractListsModel::setNextCursorStr(const QString &nextCursorStr)
{
    if (d->nextCursorStr == nextCursorStr) return;
    d->nextCursorStr = nextCursorStr;
    emit nextCursorStrChanged(nextCursorStr);
}

int AbstractListsModel::previousCursor() const
{
    return d->previousCursor;
}

void AbstractListsModel::setPreviousCursor(int previousCursor)
{
    if (d->previousCursor == previousCursor) return;
    d->previousCursor = previousCursor;
    emit previousCursorChanged(previousCursor);
}

const QString &AbstractListsModel::previousCursorStr() const
{
    return d->previousCursorStr;
}

void AbstractListsModel::setPreviousCursorStr(const QString &previousCursorStr)
{
    if (d->previousCursorStr == previousCursorStr) return;
    d->previousCursorStr = previousCursorStr;
    emit previousCursorStrChanged(previousCursorStr);
}
