#include "directmessagessent.h"
#include "../tools/oauthmanager.h"

DirectMessagesSent::DirectMessagesSent(QObject *parent)
    : AbstractDirectMessagesModel(parent)
{
}

void DirectMessagesSent::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (value.value("sender").toMap().value("id_str").toString() == OAuthManager::instance().userId()) {
        addData(value);
    }
}
