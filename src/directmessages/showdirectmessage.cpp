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
        setData(manager->getData(DataManager::DirectMessageData, id()));
        setLoading(false);
    } else {
        AbstractDirectMessageAction::exec();
    }
}
