#include "weekly.h"

class Weekly::Private
{
public:
    Private();
    QString date;
    bool exclude;
};

Weekly::Private::Private()
    : exclude(false)
{
}

Weekly::Weekly(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[QueryRole] = "query";
    roles[NameRole] = "name";
    roles[PromotedContentRole] = "promoted_content";
    roles[EventsRole] = "events";
    roles[UrlRole] = "url";
    setRoleNames(roles);
    connect(this, SIGNAL(dateChanged(QString)), this, SLOT(reload()));
}

Weekly::~Weekly()
{
    delete d;
}

void Weekly::reload()
{
    if (!date().isEmpty()) {
        AbstractTwitterModel::reload();
    }
}

void Weekly::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::Map) {
        QVariantMap trends = result.toMap().value("trends").toMap();
        foreach (const QString &trend, trends.keys()) {
            QVariantList array = trends.value(trend).toList();
            foreach (const QVariant &data, array) {
                QVariantMap map = data.toMap();
                map.insert("id_str", map.value("name").toString());
                addData(map);
            }
        }
    }
}

const QString &Weekly::date() const
{
    return d->date;
}

void Weekly::setDate(const QString &date)
{
    if (d->date == date) return;
    d->date = date;
    emit dateChanged(date);
}

bool Weekly::exclude() const
{
    return d->exclude;
}

void Weekly::setExclude(bool exclude)
{
    if (d->exclude == exclude) return;
    d->exclude = exclude;
    emit excludeChanged(exclude);
}
