#include "settings.h"

class Settings::Private
{
public:
    Private();

    bool alwaysUseHttps;
    bool discoverableByEmail;
    bool geoEnabled;
    QString language;
    bool isProtected;
    QString screenName;
    bool showAllInlineMedia;
    QVariantMap sleepTime;
    QVariantMap timeZone;
    QVariantList trendLocation;
};

Settings::Private::Private()
    : alwaysUseHttps(false)
    , discoverableByEmail(false)
    , geoEnabled(false)
    , isProtected(false)
    , showAllInlineMedia(false)
{
}

Settings::Settings(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

Settings::~Settings()
{
    delete d;
}

bool Settings::alwaysUseHttps() const
{
    return d->alwaysUseHttps;
}

void Settings::setAlwaysUseHttps(bool alwaysUseHttps)
{
    if (d->alwaysUseHttps == alwaysUseHttps) return;
    d->alwaysUseHttps = alwaysUseHttps;
    emit alwaysUseHttpsChanged(alwaysUseHttps);
}

bool Settings::discoverableByEmail() const
{
    return d->discoverableByEmail;
}

void Settings::setDiscoverableByEmail(bool discoverableByEmail)
{
    if (d->discoverableByEmail == discoverableByEmail) return;
    d->discoverableByEmail = discoverableByEmail;
    emit discoverableByEmailChanged(discoverableByEmail);
}

bool Settings::geoEnabled() const
{
    return d->geoEnabled;
}

void Settings::setGeoEnabled(bool geoEnabled)
{
    if (d->geoEnabled == geoEnabled) return;
    d->geoEnabled = geoEnabled;
    emit geoEnabledChanged(geoEnabled);
}

const QString &Settings::language() const
{
    return d->language;
}

void Settings::setLanguage(const QString &language)
{
    if (d->language == language) return;
    d->language = language;
    emit languageChanged(language);
}

bool Settings::isProtected() const
{
    return d->isProtected;
}

void Settings::setProtected(bool isProtected)
{
    if (d->isProtected == isProtected) return;
    d->isProtected = isProtected;
    emit protectedChanged(isProtected);
}

const QString &Settings::screenName() const
{
    return d->screenName;
}

void Settings::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

bool Settings::showAllInlineMedia() const
{
    return d->showAllInlineMedia;
}

void Settings::setShowAllInlineMedia(bool showAllInlineMedia)
{
    if (d->showAllInlineMedia == showAllInlineMedia) return;
    d->showAllInlineMedia = showAllInlineMedia;
    emit showAllInlineMediaChanged(showAllInlineMedia);
}

const QVariantMap &Settings::sleepTime() const
{
    return d->sleepTime;
}

void Settings::setSleepTime(const QVariantMap &sleepTime)
{
    if (d->sleepTime == sleepTime) return;
    d->sleepTime = sleepTime;
    emit sleepTimeChanged(sleepTime);
}

const QVariantList &Settings::trendLocation() const
{
    return d->trendLocation;
}

void Settings::setTrendLocation(const QVariantList &trendLocation)
{
    if (d->trendLocation == trendLocation) return;
    d->trendLocation = trendLocation;
    emit trendLocationChanged(trendLocation);
}



const QVariantMap &Settings::timeZone() const
{
    return d->timeZone;
}

void Settings::setTimeZone(const QVariantMap &timeZone)
{
    if (d->timeZone == timeZone) return;
    d->timeZone = timeZone;
    emit timeZoneChanged(timeZone);
}

