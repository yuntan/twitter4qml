/* Copyright (c) 2012-2013 Twitter4QML Project.
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

#ifndef UPDATESETTINGS_H
#define UPDATESETTINGS_H

#include "abstracttwitteraction.h"

class TWITTER4QML_EXPORT UpdateSettings : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(UpdateSettings)
    Q_PROPERTY(int trend_location_woeid READ trend_location_woeid WRITE trend_location_woeid NOTIFY trend_location_woeidChanged)
    Q_PROPERTY(bool sleep_time_enabled READ sleep_time_enabled WRITE sleep_time_enabled NOTIFY sleep_time_enabledChanged)
    Q_PROPERTY(int start_sleep_time READ start_sleep_time WRITE start_sleep_time NOTIFY start_sleep_timeChanged)
    Q_PROPERTY(int end_sleep_time READ end_sleep_time WRITE end_sleep_time NOTIFY end_sleep_timeChanged)
    Q_PROPERTY(QString time_zone READ time_zone WRITE time_zone NOTIFY time_zoneChanged)
    Q_PROPERTY(QString lang READ lang WRITE lang NOTIFY langChanged)
public:
    explicit UpdateSettings(QObject *parent = 0);

signals:
    void trend_location_woeidChanged(int trend_location_woeid);
    void sleep_time_enabledChanged(bool sleep_time_enabled);
    void start_sleep_timeChanged(int start_sleep_time);
    void end_sleep_timeChanged(int end_sleep_time);
    void time_zoneChanged(const QString &time_zone);
    void langChanged(const QString &lang);

protected:
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/account/settings.json"); }

private:
    ADD_PROPERTY(int, trend_location_woeid, int)
    ADD_PROPERTY(bool, sleep_time_enabled, bool)
    ADD_PROPERTY(int, start_sleep_time, int)
    ADD_PROPERTY(int, end_sleep_time, int)
    ADD_PROPERTY(const QString &, time_zone, QString)
    ADD_PROPERTY(const QString &, lang, QString)
};

#endif // UPDATESETTINGS_H
