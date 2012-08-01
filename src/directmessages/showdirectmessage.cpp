#include "showdirectmessage.h"
#include "../tools/datamanager.h"
#include "twitter4qml_global.h"

ShowDirectMessage::ShowDirectMessage(QObject *parent)
    : AbstractDirectMessageAction(parent)
{
}

void ShowDirectMessage::exec()
{
    DataManager *manager = DataManager::instance();
    if (manager->contains(DataManager::DirectMessageData, id())) {
        QVariantMap directMessage = manager->getData(DataManager::DirectMessageData, id());
        if (directMessage.contains(QLatin1String("entities"))) {
            setData(directMessage);
            setLoading(false);
        } else {
            AbstractDirectMessageAction::exec();
        }
    } else {
        AbstractDirectMessageAction::exec();
    }
}
