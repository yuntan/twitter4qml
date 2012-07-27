#ifndef TWEETMANAGER_H
#define TWEETMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

class TweetManager : public QObject
{
    Q_OBJECT
public:
    enum Type {

    };

    static TweetManager *instance();

    bool contains(const QString &key);
    const QVariantMap &get(const QString &key);
    void add(const QVariantMap &value);
    void remove(const QString &key);
    void set(const QString &id, const QVariantMap &value);

private:
    explicit TweetManager(QObject *parent = 0);
    Q_DISABLE_COPY(TweetManager)
    class Private;
    Private *d;
};

#endif // TWEETMANAGER_H
