#include "searchusers.h"

SearchUsers::SearchUsers(QObject *parent)
    : AbstractUsersModel(parent)
{
}

void SearchUsers::reload()
{
    if (!id().isEmpty() ) {
        AbstractTwitterModel::reload();
    }
}
