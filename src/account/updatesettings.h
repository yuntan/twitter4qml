#ifndef UPDATESETTINGS_H
#define UPDATESETTINGS_H

#include "../tools/abstracttwitteraction.h"

class UpdateSettings : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(UpdateSettings)
    Q_PROPERTY(int trend_location_woeid READ trendLocationWoeid WRITE setTrendLocationWoeid NOTIFY trendLocationWoeidChanged)
    Q_PROPERTY(bool sleep_time_enabled READ sleepTimeEnabled WRITE setSleepTimeEnabled NOTIFY sleepTimeEnabledChanged)
    Q_PROPERTY(int start_sleep_time READ startSleepTime WRITE setStartSleepTime NOTIFY startSleepTimeChanged)
    Q_PROPERTY(int end_sleep_time READ endSleepTime WRITE setEndSleepTime NOTIFY endSleepTimeChanged)
    Q_PROPERTY(QString time_zone READ timeZone WRITE setTimeZone NOTIFY timeZoneChanged)
    Q_PROPERTY(QString lang READ lang WRITE setLang NOTIFY langChanged)
public:
    explicit UpdateSettings(QObject *parent = 0);
    ~UpdateSettings();

    int trendLocationWoeid() const;
    void setTrendLocationWoeid(int trendLocationWoeid);
    bool sleepTimeEnabled() const;
    void setSleepTimeEnabled(bool sleepTimeEnabled);
    int startSleepTime() const;
    void setStartSleepTime(int startSleepTime);
    int endSleepTime() const;
    void setEndSleepTime(int endSleepTime);
    const QString &timeZone() const;
    void setTimeZone(const QString &timeZone);
    const QString &lang() const;
    void setLang(const QString &lang);

signals:
    void trendLocationWoeidChanged(int trendLocationWoeid);
    void sleepTimeEnabledChanged(bool sleepTimeEnabled);
    void startSleepTimeChanged(int startSleepTime);
    void endSleepTimeChanged(int endSleepTime);
    void timeZoneChanged(const QString &timeZone);
    void langChanged(const QString &lang);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/account/settings.json"); }

private:
    class Private;
    Private *d;
};

#endif // UPDATESETTINGS_H
