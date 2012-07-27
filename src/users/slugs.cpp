#include "slugs.h"

class Slugs::Private
{
public:
    QString lang;
};

Slugs::Slugs(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[SlugRole] = "slug";
    roles[SizeRole] = "size";
    setRoleNames(roles);
}

Slugs::~Slugs()
{
    delete d;
}

void Slugs::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        QAlgorithmsPrivate::qReverse(array.begin(), array.end());
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                QVariantMap map = result.toMap();
                map.insert("id_str", map.value("slug").toString());
                addData(map);
            }
        }
    }
}

const QString &Slugs::lang() const
{
    return d->lang;
}

void Slugs::setLang(const QString &lang)
{
    if (d->lang == lang) return;
    d->lang = lang;
    emit langChanged(lang);
}
