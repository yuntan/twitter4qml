#include "updatesettings.h"

class UpdateSettings::Private
{
public:
    Private();

    int trendLocationWoeid;
    bool sleepTimeEnabled;
    int startSleepTime;
    int endSleepTime;
    QString timeZone;
    QString lang;
};

UpdateSettings::Private::Private()
    : trendLocationWoeid(0)
    , sleepTimeEnabled(false)
    , startSleepTime(0)
    , endSleepTime(0)
{
}

UpdateSettings::UpdateSettings(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

UpdateSettings::~UpdateSettings()
{
    delete d;
}

int UpdateSettings::trendLocationWoeid() const
{
    return d->trendLocationWoeid;
}

void UpdateSettings::setTrendLocationWoeid(int trendLocationWoeid)
{
    if (d->trendLocationWoeid == trendLocationWoeid) return;
    d->trendLocationWoeid = trendLocationWoeid;
    emit trendLocationWoeidChanged(trendLocationWoeid);
}

bool UpdateSettings::sleepTimeEnabled() const
{
    return d->sleepTimeEnabled;
}

void UpdateSettings::setSleepTimeEnabled(bool sleepTimeEnabled)
{
    if (d->sleepTimeEnabled == sleepTimeEnabled) return;
    d->sleepTimeEnabled = sleepTimeEnabled;
    emit sleepTimeEnabledChanged(sleepTimeEnabled);
}

int UpdateSettings::startSleepTime() const
{
    return d->startSleepTime;
}

void UpdateSettings::setStartSleepTime(int startSleepTime)
{
    if (d->startSleepTime == startSleepTime) return;
    d->startSleepTime = startSleepTime;
    emit startSleepTimeChanged(startSleepTime);
}

int UpdateSettings::endSleepTime() const
{
    return d->endSleepTime;
}

void UpdateSettings::setEndSleepTime(int endSleepTime)
{
    if (d->endSleepTime == endSleepTime) return;
    d->endSleepTime = endSleepTime;
    emit endSleepTimeChanged(endSleepTime);
}

const QString &UpdateSettings::timeZone() const
{
    return d->timeZone;
}

void UpdateSettings::setTimeZone(const QString &timeZone)
{
    if (d->timeZone == timeZone) return;
    d->timeZone = timeZone;
    emit timeZoneChanged(timeZone);
}

const QString &UpdateSettings::lang() const
{
    return d->lang;
}

void UpdateSettings::setLang(const QString &lang)
{
    if (d->lang == lang) return;
    d->lang = lang;
    emit langChanged(lang);
}
