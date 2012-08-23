#include "favorites.h"

Favorites::Favorites(QObject *parent)
    : AbstractStatusesModel(parent)
{
}

void Favorites::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (value.value("favorited").toBool()) {
        addData(value);
    }
}

void Favorites::dataChanged(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (value.value("favorited").toBool()) {
        addData(value);
    } else {
        removeData(key);
    }
}
