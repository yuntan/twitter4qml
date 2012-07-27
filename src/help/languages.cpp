#include "languages.h"

Languages::Languages(QObject *parent)
    : AbstractTwitterModel(parent)
{
    QHash<int, QByteArray> roles;
    roles[CodeRole] = "code";
    roles[NameRole] = "name";
    roles[StatusRole] = "status";
    setRoleNames(roles);
}

void Languages::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                QVariantMap map = result.toMap();
                map.insert("id_str", map.value("name").toString());
                addData(map);
            }
        }
    }
}
