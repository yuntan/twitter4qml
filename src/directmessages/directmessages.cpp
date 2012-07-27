#include "directmessages.h"
#include "../tools/oauthmanager.h"

DirectMessages::DirectMessages(QObject *parent)
    : AbstractDirectMessagesModel(parent)
{
}

void DirectMessages::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (value.value("recipient").toMap().value("id_str").toString() == OAuthManager::instance().userId()) {
        addData(value);
    }
}
