#include "showrelatedresults.h"
#include "../statuses/status.h"

ShowRelatedResults::ShowRelatedResults(QObject *parent)
    : AbstractStatusesModel(parent)
{
}

static void qvariant_debug(const QVariant &value, int level = 0, QString prefix = QString())
{
    QVariantList list;
    QVariantMap map;
    switch (value.type()) {
    case QVariant::List:
        list = value.toList();
        foreach (const QVariant &v, list) {
            qvariant_debug(v, level + 1, prefix);
        }
        break;
    case QVariant::Map:
        map = value.toMap();
        foreach (const QString &key, map.keys()) {
            qvariant_debug(map[key], level + 1, key);
        }
        break;
    default:
        qDebug() << QString(level * 2, ' ') << prefix << value;
    }
}

void ShowRelatedResults::parseDone(const QVariant &result)
{
    if (result.type() != QVariant::List) {
        DEBUG();
        qvariant_debug(result);
        DEBUG();
        return;
    }
    QVariantList list = result.toList();
    if (list.isEmpty())
        return;
    if (list.length() > 1) {
        DEBUG();
        qvariant_debug(result);
        DEBUG();
        return;
    }
    QVariantMap map = list.first().toMap();
    if (map.value("groupName").toString() != "TweetsWithConversation" || map.value("resultType").toString() != "Tweet") {
        DEBUG();
        qvariant_debug(map);
        DEBUG();
        return;
    }
    if (map.value("results").type() != QVariant::List) {
        DEBUG();
        qvariant_debug(map);
        DEBUG();
        return;
    }
    QVariantList results = map.value("results").toList();
    foreach (const QVariant &v1, results) {
        QVariantMap result = v1.toMap();
        DEBUG() << result.value("annotations");
        if (result.value("kind").toString() != "Tweet" || result.value("score").toInt() != 1) {
            DEBUG();
            qvariant_debug(result);
            DEBUG();
            return;
        }
        QVariantMap value = result.value("value").toMap();
        addData(Status::parse(value));
    }
}
