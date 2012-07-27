#include "usertimeline.h"
#include "../tools/oauthmanager.h"

UserTimeline::UserTimeline(QObject *parent)
    : AbstractStatusesModel(parent)
{
}

void UserTimeline::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    QString id_str = value.value("user").toMap().value("id_str").toString();
    if (userId().isEmpty() && id_str == OAuthManager::instance().userId()) {
        addData(value);
    } else if (id_str == userId()) {
        addData(value);
    }
}
