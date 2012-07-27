#include "lookupusers.h"

LookupUsers::LookupUsers(QObject *parent)
    : AbstractUsersModel(parent)
{
}

void LookupUsers::reload()
{
    if (!id().isEmpty() || !screenName().isEmpty()) {
        AbstractTwitterModel::reload();
    }
}
