#include "abstractidsmodel.h"

class AbstractIdsModel::Private
{
public:
    Private();

    QString id;
    int count;
    int page;
    bool stringifyIds;
};

AbstractIdsModel::Private::Private()
    : count(0)
    , page(0)
    , stringifyIds(true)
{
}

AbstractIdsModel::AbstractIdsModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[IdStrRole] = "id_str";
    setRoleNames(roles);
}

AbstractIdsModel::~AbstractIdsModel()
{
    delete d;
}

AbstractTwitterModel::AuthorizeBy AbstractIdsModel::authenticationMethod() const
{
    return AuthorizeByUrl;
}

QString AbstractIdsModel::httpMethod() const
{
    return "GET";
}

void AbstractIdsModel::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Int) {
                QVariantMap map;
                map.insert("id", result.toInt());
                map.insert("id_str", result.toString());
                addData(map);
            } else if (result.type() == QVariant::String) {
                QVariantMap map;
                map.insert("id", result.toInt());
                map.insert("id_str", result.toString());
                addData(map);
            } else {
                DEBUG() << result.type() << result;
            }
        }
    } else {
        DEBUG() << result.type() << result;
    }
}

const QString &AbstractIdsModel::id() const
{
    return d->id;
}

void AbstractIdsModel::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

int AbstractIdsModel::count() const
{
    return d->count;
}

void AbstractIdsModel::setCount(int count)
{
    if (d->count == count) return;
    d->count = count;
    emit countChanged(count);
}

int AbstractIdsModel::page() const
{
    return d->page;
}

void AbstractIdsModel::setPage(int page)
{
    if (d->page == page) return;
    d->page = page;
    emit pageChanged(page);
}

bool AbstractIdsModel::stringifyIds() const
{
    return d->stringifyIds;
}

void AbstractIdsModel::setStringifyIds(bool stringifyIds)
{
    if (d->stringifyIds == stringifyIds) return;
    d->stringifyIds = stringifyIds;
    emit stringifyIdsChanged(stringifyIds);
}
