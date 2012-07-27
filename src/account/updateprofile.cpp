#include "updateprofile.h"

class UpdateProfile::Private
{
public:
    Private();

    QString name;
    QString url;
    QString location;
    QString description;
    bool includeEntities;
    bool skipStatus;
};

UpdateProfile::Private::Private()
    : includeEntities(true)
    , skipStatus(false)
{
}

UpdateProfile::UpdateProfile(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

UpdateProfile::~UpdateProfile()
{
    delete d;
}

const QString &UpdateProfile::name() const
{
    return d->name;
}

void UpdateProfile::setName(const QString &name)
{
    if (d->name == name) return;
    d->name = name;
    emit nameChanged(name);
}

const QString &UpdateProfile::url() const
{
    return d->url;
}

void UpdateProfile::setUrl(const QString &url)
{
    if (d->url == url) return;
    d->url = url;
    emit urlChanged(url);
}

const QString &UpdateProfile::location() const
{
    return d->location;
}

void UpdateProfile::setLocation(const QString &location)
{
    if (d->location == location) return;
    d->location = location;
    emit locationChanged(location);
}

const QString &UpdateProfile::description() const
{
    return d->description;
}

void UpdateProfile::setDescription(const QString &description)
{
    if (d->description == description) return;
    d->description = description;
    emit descriptionChanged(description);
}

bool UpdateProfile::includeEntities() const
{
    return d->includeEntities;
}

void UpdateProfile::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}

bool UpdateProfile::skipStatus() const
{
    return d->skipStatus;
}

void UpdateProfile::setSkipStatus(bool skipStatus)
{
    if (d->skipStatus == skipStatus) return;
    d->skipStatus = skipStatus;
    emit skipStatusChanged(skipStatus);
}
