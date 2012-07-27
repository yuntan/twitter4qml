#include "showlist.h"
#include "../tools/datamanager.h"

ShowList::ShowList(QObject *parent)
    : AbstractListAction(parent)
{
}

void ShowList::exec()
{
    DataManager *manager = DataManager::instance();
    if (manager->contains(DataManager::ListData, listId())) {
        setData(manager->getData(DataManager::ListData, listId()));
        setLoading(false);
    } else {
        AbstractListAction::exec();
    }
}
