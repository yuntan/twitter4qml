#include "showstatus.h"
#include "../tools/datamanager.h"
#include "twitter4qml_global.h"

ShowStatus::ShowStatus(QObject *parent)
    : AbstractStatusAction(parent)
{
}

void ShowStatus::exec()
{
    DataManager *manager = DataManager::instance();
    if (manager->contains(DataManager::StatusData, id())) {
        QVariantMap data = manager->getData(DataManager::StatusData, id());
        if (data.contains("in_reply_to_status_id")) {
            setData(data);
            setLoading(false);
        } else {
            AbstractStatusAction::exec();
        }
    } else {
        AbstractStatusAction::exec();
    }
}
