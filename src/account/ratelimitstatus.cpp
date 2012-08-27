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

#include "ratelimitstatus.h"

class RateLimitStatus::Private
{
public:
    Private();

    int remainingHits;
    int resetTimeInSeconds;
    int hourlyLimit;
    QString resetTime;
    QVariantMap photos;
};

RateLimitStatus::Private::Private()
    : remainingHits(0)
    , resetTimeInSeconds(0)
    , hourlyLimit(0)
{
}

RateLimitStatus::RateLimitStatus(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

RateLimitStatus::~RateLimitStatus()
{
    delete d;
}

int RateLimitStatus::remainingHits() const
{
    return d->remainingHits;
}

void RateLimitStatus::setRemainingHits(int remainingHits)
{
    if (d->remainingHits == remainingHits) return;
    d->remainingHits = remainingHits;
    emit remainingHitsChanged(remainingHits);
}

int RateLimitStatus::resetTimeInSeconds() const
{
    return d->resetTimeInSeconds;
}

void RateLimitStatus::setResetTimeInSeconds(int resetTimeInSeconds)
{
    if (d->resetTimeInSeconds == resetTimeInSeconds) return;
    d->resetTimeInSeconds = resetTimeInSeconds;
    emit resetTimeInSecondsChanged(resetTimeInSeconds);
}

int RateLimitStatus::hourlyLimit() const
{
    return d->hourlyLimit;
}

void RateLimitStatus::setHourlyLimit(int hourlyLimit)
{
    if (d->hourlyLimit == hourlyLimit) return;
    d->hourlyLimit = hourlyLimit;
    emit hourlyLimitChanged(hourlyLimit);
}

const QString &RateLimitStatus::resetTime() const
{
    return d->resetTime;
}

void RateLimitStatus::setResetTime(const QString &resetTime)
{
    if (d->resetTime == resetTime) return;
    d->resetTime = resetTime;
    emit resetTimeChanged(resetTime);
}

const QVariantMap &RateLimitStatus::photos() const
{
    return d->photos;
}

void RateLimitStatus::setPhotos(const QVariantMap &photos)
{
    if (d->photos == photos) return;
    d->photos = photos;
    emit photosChanged(photos);
}
