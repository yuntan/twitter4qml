#include "trends.h"
#include <QtCore/qalgorithms.h>

class Trends::Private
{
public:
    Private();
    int woeid;
    bool exclude;
};

Trends::Private::Private()
    : woeid(0)
    , exclude(false)
{
}

Trends::Trends(QObject *parent)
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
    connect(this, SIGNAL(woeidChanged(int)), this, SLOT(reload()));
}

Trends::~Trends()
{
    delete d;
}

void Trends::reload()
{
    if (woeid() > 0) {
        AbstractTwitterModel::reload();
    }
}

void Trends::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                QVariantMap map = result.toMap();
                if (map.contains("trends") && map.value("trends").type() == QVariant::List) {
                    QVariantList trends = map.value("trends").toList();
                    QAlgorithmsPrivate::qReverse(trends.begin(), trends.end());
                    foreach (const QVariant &trend, trends) {
                        QVariantMap t = trend.toMap();
                        t.insert("id_str", t.value("name").toString());
                        addData(t);
                    }
                }
            }
        }
    }
}

int Trends::woeid() const
{
    return d->woeid;
}

void Trends::setWoeid(int woeid)
{
    if (d->woeid == woeid) return;
    d->woeid = woeid;
    emit woeidChanged(woeid);
}

bool Trends::exclude() const
{
    return d->exclude;
}

void Trends::setExclude(bool exclude)
{
    if (d->exclude == exclude) return;
    d->exclude = exclude;
    emit excludeChanged(exclude);
}
