#include "listssubscriptions.h"

ListsSubscriptions::ListsSubscriptions(QObject *parent)
    : AbstractListsModel(parent)
{
}

void ListsSubscriptions::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::Map) {
        QVariantMap object = result.toMap();
        if (object.contains("lists") && object.value("lists").type() == QVariant::List) {
            AbstractListsModel::parseDone(object.value("lists"));
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
