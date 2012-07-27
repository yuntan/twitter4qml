#include "daily.h"

class Daily::Private
{
public:
    Private();
    QString date;
    bool exclude;
};

Daily::Private::Private()
    : exclude(false)
{
}

Daily::Daily(QObject *parent)
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

Daily::~Daily()
{
    delete d;
}

void Daily::reload()
{
    if (!date().isEmpty()) {
        AbstractTwitterModel::reload();
    }
}

void Daily::parseDone(const QVariant &result)
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

const QString &Daily::date() const
{
    return d->date;
}

void Daily::setDate(const QString &date)
{
    if (d->date == date) return;
    d->date = date;
    emit dateChanged(date);
}

bool Daily::exclude() const
{
    return d->exclude;
}

void Daily::setExclude(bool exclude)
{
    if (d->exclude == exclude) return;
    d->exclude = exclude;
    emit excludeChanged(exclude);
}
