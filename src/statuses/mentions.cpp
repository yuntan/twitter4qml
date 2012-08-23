#include "mentions.h"
#include "../tools/oauthmanager.h"

Mentions::Mentions(QObject *parent)
    : AbstractStatusesModel(parent)
{
}

void Mentions::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    QVariantMap entities = value.value("entities").toMap();
    QVariantList user_mentions = entities.value("user_mentions").toList();
    QString idStr = OAuthManager::instance().userId();
    foreach (const QVariant &user_mention, user_mentions) {
        if (user_mention.toMap().value("id_str").toString() == idStr) {
            addData(value);
            break;
        }
    }
}
