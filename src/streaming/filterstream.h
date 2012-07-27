#ifndef FILTERSTREAM_H
#define FILTERSTREAM_H

#include "../statuses/abstractstatusesmodel.h"

class FilterStream : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString delimited READ delimited WRITE setDelimited NOTIFY delimitedChanged)
    Q_PROPERTY(QString follow READ follow WRITE setFollow NOTIFY followChanged)
    Q_PROPERTY(QString track READ track WRITE setTrack NOTIFY trackChanged)
    Q_DISABLE_COPY(FilterStream)
public:
    explicit FilterStream(QObject *parent = 0);
    ~FilterStream();

    const QString &delimited() const;
    void setDelimited(const QString &delimited);
    const QString &follow() const;
    void setFollow(const QString &follow);
    const QString &track() const;
    void setTrack(const QString &track);

public slots:
    void reload();

signals:
    void delimitedChanged(const QString &delimited);
    void followChanged(const QString &follow);
    void trackChanged(const QString &track);

protected:
    bool isStreaming() const { return true; }
    QUrl api() const { return QUrl("https://stream.twitter.com/1/statuses/filter.json"); }
    QString httpMethod() const { return "POST"; }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // FILTERSTREAM_H
