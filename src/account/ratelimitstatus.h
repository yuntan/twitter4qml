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
