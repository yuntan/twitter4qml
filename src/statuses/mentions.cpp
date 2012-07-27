#include "mentions.h"
#include "../tools/oauthmanager.h"

Mentions::Mentions(QObject *parent)
    : AbstractStatusesModel(parent)
{
}

void Mentions::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (value.value("text").toString().contains(QString("@%1").arg(OAuthManager::instance().screenName()))) {
        addData(value);
    }
}
