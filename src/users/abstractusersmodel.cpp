#include "abstractusersmodel.h"

class AbstractUsersModel::Private
{
public:
    Private();

    QString id;
    QString screenName;
    bool includeEntities;
    int count;
    int page;
    QString cursor;

    int nextCursor;
    QString nextCursorStr;
    int previousCursor;
    QString previousCursorStr;
};

AbstractUsersModel::Private::Private()
    : includeEntities(false)
    , count(0)
    , page(0)
    , nextCursor(0)
    , previousCursor(0)
{
}

AbstractUsersModel::AbstractUsersModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[ContributorsEnabledRole] = "contributors_enabled";
    roles[CreatedAtRole] = "created_at";
    roles[DefaultProfileRole] = "default_profile";
    roles[DefaultProfileImageRole] = "default_profile_image";
    roles[DescriptionRole] = "description";
    roles[FavouritesCountRole] = "favourites_count";
    roles[FollowRequestSentRole] = "follow_request_sent";
    roles[FollowersCountRole] = "followers_count";
    roles[FollowingRole] = "following";
    roles[FriendsCountRole] = "friends_count";
    roles[GeoEnabledRole] = "geo_enabled";
    roles[IdRole] = "id";
    roles[IdStrRole] = "id_str";
    roles[IsTranslatorRole] = "is_translator";
    roles[LangRole] = "lang";
    roles[ListedCountRole] = "listed_count";
    roles[LocationRole] = "location";
    roles[NameRole] = "name";
    roles[NotificationsRole] = "notifications";
    roles[ProfileBackgroundColorRole] = "profile_background_color";
    roles[ProfileBackgroundImageUrlRole] = "profile_background_image_url";
    roles[ProfileBackgroundImageUrlHttpsRole] = "profile_background_image_url_https";
    roles[ProfileBackgroundTileRole] = "profile_background_tile";
    roles[ProfileImageUrlRole] = "profile_image_url";
    roles[ProfileImageUrlHttpsRole] = "profile_image_url_https";
    roles[ProfileLinkColorRole] = "profile_link_color";
    roles[ProfileSidebarBorderColorRole] = "profile_sidebar_border_color";
    roles[ProfileSidebarFillColorRole] = "profile_sidebar_fill_color";
    roles[ProfileTextColorRole] = "profile_text_color";
    roles[ProfileUseBackgroundImageRole] = "profile_use_background_image";
    roles[ProtectedRole] = "protected";
    roles[ScreenNameRole] = "screen_name";
    roles[ShowAllInlineMediaRole] = "show_all_inline_media";
    roles[StatusesCountRole] = "statuses_count";
    roles[TimeZoneRole] = "time_zone";
    roles[UrlRole] = "url";
    roles[UtcOffsetRole] = "utc_offset";
    roles[VerifiedRole] = "verified";
    setRoleNames(roles);
}

AbstractUsersModel::~AbstractUsersModel()
{
    delete d;
}

void AbstractUsersModel::reload()
{
    setNextCursor(0);
    setNextCursorStr(QString());
    setPreviousCursor(0);
    setPreviousCursorStr(QString());
    AbstractTwitterModel::reload();
}

void AbstractUsersModel::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        QAlgorithmsPrivate::qReverse(array.begin(), array.end());
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                addData(result.toMap());
            }
        }
    }
}

const QString &AbstractUsersModel::id() const
{
    return d->id;
}

void AbstractUsersModel::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

const QString &AbstractUsersModel::screenName() const
{
    return d->screenName;
}

void AbstractUsersModel::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

bool AbstractUsersModel::includeEntities() const
{
    return d->includeEntities;
}

void AbstractUsersModel::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}

int AbstractUsersModel::count() const
{
    return d->count;
}

void AbstractUsersModel::setCount(int count)
{
    if (d->count == count) return;
    d->count = count;
    emit countChanged(count);
}

int AbstractUsersModel::page() const
{
    return d->page;
}

void AbstractUsersModel::setPage(int page)
{
    if (d->page == page) return;
    d->page = page;
    emit pageChanged(page);
}

const QString &AbstractUsersModel::cursor() const
{
    return d->cursor;
}

void AbstractUsersModel::setCursor(const QString &cursor)
{
    if (d->cursor == cursor) return;
    d->cursor = cursor;
    emit cursorChanged(cursor);
}

int AbstractUsersModel::nextCursor() const
{
    return d->nextCursor;
}

void AbstractUsersModel::setNextCursor(int nextCursor)
{
    if (d->nextCursor == nextCursor) return;
    d->nextCursor = nextCursor;
    emit nextCursorChanged(nextCursor);
}

const QString &AbstractUsersModel::nextCursorStr() const
{
    return d->nextCursorStr;
}

void AbstractUsersModel::setNextCursorStr(const QString &nextCursorStr)
{
    if (d->nextCursorStr == nextCursorStr) return;
    d->nextCursorStr = nextCursorStr;
    emit nextCursorStrChanged(nextCursorStr);
}

int AbstractUsersModel::previousCursor() const
{
    return d->previousCursor;
}

void AbstractUsersModel::setPreviousCursor(int previousCursor)
{
    if (d->previousCursor == previousCursor) return;
    d->previousCursor = previousCursor;
    emit previousCursorChanged(previousCursor);
}

const QString &AbstractUsersModel::previousCursorStr() const
{
    return d->previousCursorStr;
}

void AbstractUsersModel::setPreviousCursorStr(const QString &previousCursorStr)
{
    if (d->previousCursorStr == previousCursorStr) return;
    d->previousCursorStr = previousCursorStr;
    emit previousCursorStrChanged(previousCursorStr);
}
