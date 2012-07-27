#include "favorites.h"

Favorites::Favorites(QObject *parent)
    : AbstractStatusesModel(parent)
{
}

void Favorites::dataChanged(const QString &key, const QVariantMap &value)
{
    bool favorited = value.value("favorited").toBool();
    DEBUG() << favorited;
    if (favorited) {
        addData(value);
    } else {
        removeData(key);
    }
}
