#include "abstractfriendshipidsmodel.h"

#include <QtCore/QTimer>

class AbstractFriendshipIdsModel::Private
{
public:
    Private();

    QString userId;
    QString screenName;
    QString cursor;
    bool stringifyIds;

    int nextCursor;
    QString nextCursorStr;
    int previousCursor;
    QString previousCursorStr;

    QTimer timer;
};

AbstractFriendshipIdsModel::Private::Private()
    : stringifyIds(true)
    , nextCursor(0)
    , previousCursor(0)
{
}

AbstractFriendshipIdsModel::AbstractFriendshipIdsModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[IdStrRole] = "id_str";
    setRoleNames(roles);

    connect(&d->timer, SIGNAL(timeout()), this, SLOT(reload()));
    d->timer.setSingleShot(true);
    d->timer.setInterval(0);

    connect(this, SIGNAL(userIdChanged(QString)), &d->timer, SLOT(start()));
    connect(this, SIGNAL(screenNameChanged(QString)), &d->timer, SLOT(start()));
}

AbstractFriendshipIdsModel::~AbstractFriendshipIdsModel()
{
    delete d;
}

void AbstractFriendshipIdsModel::reload() {
    if (!userId().isEmpty() || !screenName().isEmpty()) {
        AbstractTwitterModel::reload();
    }
}

void AbstractFriendshipIdsModel::parseDone(const QVariant &data)
{
    DEBUG() << data;
    if (data.type() == QVariant::Map) {
        QVariantMap object = data.toMap();
        if (object.contains("ids") && object.value("ids").type() == QVariant::List) {
            QVariantList results = object.value("ids").toList();
            foreach (const QVariant &result, results) {
                QVariantMap map;
                switch(result.type()) {
                case QVariant::Int:
                    map.insert("id", result);
                    addData(map);
                    break;
                case QVariant::String:
                    map.insert("id_str", result);
                    addData(map);
                    break;
                default:
                    break;
                }
            }
        } else {
            DEBUG() << data;
        }
        if (object.contains("next_cursor"))
            setNextCursor(object.value("next_cursor").toInt());
        if (object.contains("next_cursor_str"))
            setNextCursorStr(object.value("next_cursor_str").toString());
        if (object.contains("previous_cursor"))
            setPreviousCursor(object.value("previous_cursor").toInt());
        if (object.contains("previous_cursor_str"))
            setPreviousCursorStr(object.value("previous_cursor_str").toString());
    }
}

const QString &AbstractFriendshipIdsModel::userId() const
{
    return d->userId;
}

void AbstractFriendshipIdsModel::setUserId(const QString &userId)
{
    if (d->userId == userId) return;
    d->userId = userId;
    emit userIdChanged(userId);
}

const QString &AbstractFriendshipIdsModel::screenName() const
{
    return d->screenName;
}

void AbstractFriendshipIdsModel::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

const QString &AbstractFriendshipIdsModel::cursor() const
{
    return d->cursor;
}

void AbstractFriendshipIdsModel::setCursor(const QString &cursor)
{
    if (d->cursor == cursor) return;
    d->cursor = cursor;
    emit cursorChanged(cursor);
}

bool AbstractFriendshipIdsModel::stringifyIds() const
{
    return d->stringifyIds;
}

void AbstractFriendshipIdsModel::setStringifyIds(bool stringifyIds)
{
    if (d->stringifyIds == stringifyIds) return;
    d->stringifyIds = stringifyIds;
    emit stringifyIdsChanged(stringifyIds);
}

int AbstractFriendshipIdsModel::nextCursor() const
{
    return d->nextCursor;
}

void AbstractFriendshipIdsModel::setNextCursor(int nextCursor)
{
    if (d->nextCursor == nextCursor) return;
    d->nextCursor = nextCursor;
    emit nextCursorChanged(nextCursor);
}

const QString &AbstractFriendshipIdsModel::nextCursorStr() const
{
    return d->nextCursorStr;
}

void AbstractFriendshipIdsModel::setNextCursorStr(const QString &nextCursorStr)
{
    if (d->nextCursorStr == nextCursorStr) return;
    d->nextCursorStr = nextCursorStr;
    emit nextCursorStrChanged(nextCursorStr);
}

int AbstractFriendshipIdsModel::previousCursor() const
{
    return d->previousCursor;
}

void AbstractFriendshipIdsModel::setPreviousCursor(int previousCursor)
{
    if (d->previousCursor == previousCursor) return;
    d->previousCursor = previousCursor;
    emit previousCursorChanged(previousCursor);
}

const QString &AbstractFriendshipIdsModel::previousCursorStr() const
{
    return d->previousCursorStr;
}

void AbstractFriendshipIdsModel::setPreviousCursorStr(const QString &previousCursorStr)
{
    if (d->previousCursorStr == previousCursorStr) return;
    d->previousCursorStr = previousCursorStr;
    emit previousCursorStrChanged(previousCursorStr);
}
