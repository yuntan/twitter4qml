#ifndef RATELIMITSTATUS_H
#define RATELIMITSTATUS_H

#include "../tools/abstracttwitteraction.h"

class RateLimitStatus : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(RateLimitStatus)
    Q_PROPERTY(int remaining_hits READ remainingHits WRITE setRemainingHits NOTIFY remainingHitsChanged DESIGNABLE false USER true)
    Q_PROPERTY(int reset_time_in_seconds READ resetTimeInSeconds WRITE setResetTimeInSeconds NOTIFY resetTimeInSecondsChanged DESIGNABLE false USER true)
    Q_PROPERTY(int hourly_limit READ hourlyLimit WRITE setHourlyLimit NOTIFY hourlyLimitChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString reset_time READ resetTime WRITE setResetTime NOTIFY resetTimeChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantMap photos READ photos WRITE setPhotos NOTIFY photosChanged DESIGNABLE false USER true)
public:
    explicit RateLimitStatus(QObject *parent = 0);
    ~RateLimitStatus();

    int remainingHits() const;
    void setRemainingHits(int remainingHits);
    int resetTimeInSeconds() const;
    void setResetTimeInSeconds(int resetTimeInSeconds);
    int hourlyLimit() const;
    void setHourlyLimit(int hourlyLimit);
    const QString &resetTime() const;
    void setResetTime(const QString &resetTime);
    const QVariantMap &photos() const;
    void setPhotos(const QVariantMap &photos);

signals:
    void remainingHitsChanged(int remainingHits);
    void resetTimeInSecondsChanged(int resetTimeInSeconds);
    void hourlyLimitChanged(int hourlyLimit);
    void resetTimeChanged(const QString &resetTime);
    void photosChanged(const QVariantMap &photos);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/account/rate_limit_status.json"); }
    QString httpMethod() const { return "GET"; }

private:
    class Private;
    Private *d;
};

#endif // RATELIMITSTATUS_H
