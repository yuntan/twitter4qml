#ifndef NORETWEETIDS_H
#define NORETWEETIDS_H

#include "../statuses/abstractidsmodel.h"

class NoRetweetIds : public AbstractIdsModel
{
    Q_OBJECT
    Q_PROPERTY(bool stringify_ids READ stringifyIds WRITE setStringifyIds NOTIFY stringifyIdsChanged)
public:
    explicit NoRetweetIds(QObject *parent = 0);
    ~NoRetweetIds();

    bool stringifyIds() const;
    void setStringifyIds(bool stringifyIds);

signals:
    void stringifyIdsChanged(bool stringifyIds);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/friendships/no_retweet_ids.json"); }
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    void parseDone(const QVariant &result);

private:
    Q_DISABLE_COPY(NoRetweetIds)
    class Private;
    Private *d;
};

#endif // NORETWEETIDS_H
