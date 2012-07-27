#include "tweetmanager.h"

class TweetManager::Private : public QObject
{
    Q_OBJECT
public:
    Private(TweetManager *parent);

private:
    TweetManager *q;
};

TweetManager::Private::Private(TweetManager *parent)
    : QObject(parent)
    , q(parent)
{

}

TweetManager *TweetManager::instance()
{
    static TweetManager ret;
    return &ret;
}

TweetManager::TweetManager(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

#include "tweetmanager.moc"
