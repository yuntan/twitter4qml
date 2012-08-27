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

