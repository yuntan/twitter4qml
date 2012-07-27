#include "showuser.h"
#include "../tools/datamanager.h"

ShowUser::ShowUser(QObject *parent)
    : AbstractUserAction(parent)
{
}

void ShowUser::exec()
{
    DataManager *manager = DataManager::instance();
    if (!userId().isEmpty() && manager->contains(DataManager::UserData, userId())) {
        QVariantMap user = manager->getData(DataManager::UserData, userId());
        if (user.value("description").isNull()) {
            AbstractUserAction::exec();
        } else {
            setData(user);
            setLoading(false);
        }
    } else {
        AbstractUserAction::exec();
    }
}
