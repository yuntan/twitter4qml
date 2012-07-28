#include "userstream.h"
#include "../statuses/status.h"
#include "../directmessages/directmessage.h"

class UserStream::Private
{
public:
    Private();
    QString delimited;
    QString replies;
    QList<int> friends;
};

UserStream::Private::Private() : delimited("length") {}

UserStream::UserStream(QObject *parent)
    : AbstractStatusesModel(parent)
    , d(new Private)
{
    setPushOrder(PushOlderToNewer);
}

UserStream::~UserStream()
{
    delete d;
}

void UserStream::parseDone(const QVariant &result)
{
    switch (result.type()) {
    case QVariant::Map: {
        QVariantMap object = result.toMap();
        if (object.keys().contains("text")) {
            addData(Status::parse(result.toMap()));
        } else if (object.keys().contains("friends")) {
            d->friends.clear();
            QVariantList list = object.value("friends").toList();
            foreach (const QVariant &id, list) {
                d->friends.append(id.toInt());
            }
            emit friendsChanged(d->friends);
        } else if (object.keys().contains("event")) {
            DEBUG() << object.value("event").toString() << object;
            if (object.value("event").toString() == "follow") {
                emit followedBy(Status::parse(object));
            } else if (object.value("event").toString() == "favorite") {
                emit favorited(Status::parse(object));
            } else if (object.value("event").toString() == "unfavorite") {
                emit unfavorited(Status::parse(object));
            } else {
                DEBUG() << object.value("event").toString() << object;
            }
        } else if (object.keys().contains("direct_message")) {
            QVariantMap directMessage = object.value("direct_message").toMap();
            DEBUG() << directMessage;
            DataManager::instance()->addData(DataManager::DirectMessageData, directMessage.value("id_str").toString(), DirectMessage::parse(directMessage));
        } else if (object.keys().contains("delete")) {
            DataManager::instance()->removeData(DataManager::StatusData, object.value("delete").toMap().value("status").toMap().value("id_str").toString());
        } else {
            DEBUG() << object;
        }
    }
        break;
    default:
        DEBUG() << result;
        break;
    }
}

const QString &UserStream::delimited() const
{
    return d->delimited;
}

void UserStream::setDelimited(const QString &delimited)
{
    if (d->delimited == delimited) return;
    d->delimited = delimited;
    emit delimitedChanged(delimited);
}

const QString &UserStream::replies() const
{
    return d->replies;
}

void UserStream::setReplies(const QString &replies)
{
    if (d->replies == replies) return;
    d->replies = replies;
    emit repliesChanged(replies);
}

const QList<int> &UserStream::friends() const
{
    return d->friends;
}
