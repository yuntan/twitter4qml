/* Copyright (c) 2012 Twitter4QML Project.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Twitter4QML nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL TWITTER4QML BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
