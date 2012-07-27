#include "listmembers.h"

class ListMembers::Private
{
public:
    QString slug;
};

ListMembers::ListMembers(QObject *parent)
    : AbstractUsersModel(parent)
    , d(new Private)
{
}

ListMembers::~ListMembers()
{
    delete d;
}

void ListMembers::reload()
{
    if (!id().isEmpty() || (!screenName().isEmpty() && !slug().isEmpty())) {
        AbstractUsersModel::reload();
    }
}

void ListMembers::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::Map) {
        QVariantMap object = result.toMap();
        if (object.contains("users") && object.value("users").type() == QVariant::List) {
            AbstractUsersModel::parseDone(object.value("users"));
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

const QString &ListMembers::slug() const
{
    return d->slug;
}

void ListMembers::setSlug(const QString &slug)
{
    if (d->slug == slug) return;
    d->slug = slug;
    emit slugChanged(slug);
}
