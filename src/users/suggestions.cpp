#include "suggestions.h"

class Suggestions::Private
{
public:
    QString slug;
    QString lang;
};

Suggestions::Suggestions(QObject *parent)
    : AbstractUsersModel(parent)
    , d(new Private)
{
}

Suggestions::~Suggestions()
{
    delete d;
}

void Suggestions::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    if (result.type() == QVariant::Map) {
        QVariantMap map = result.toMap();
        AbstractUsersModel::parseDone(map.value("users"));
    }
}

const QString &Suggestions::slug() const
{
    return d->slug;
}

void Suggestions::setSlug(const QString &slug)
{
    if (d->slug == slug) return;
    d->slug = slug;
    emit slugChanged(slug);
}

const QString &Suggestions::lang() const
{
    return d->lang;
}

void Suggestions::setLang(const QString &lang)
{
    if (d->lang == lang) return;
    d->lang = lang;
    emit langChanged(lang);
}
