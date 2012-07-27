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
