#include "filterstream.h"
#include "../statuses/status.h"

class FilterStream::Private
{
public:
    Private();
    QString delimited;
    QString follow;
    QString track;
};

FilterStream::Private::Private() : delimited("length") {}

FilterStream::FilterStream(QObject *parent)
    : AbstractStatusesModel(parent)
    , d(new Private)
{
    connect(this, SIGNAL(trackChanged(QString)), this, SLOT(reload()), Qt::QueuedConnection);
    setPushOrder(PushOlderToNewer);
}

FilterStream::~FilterStream()
{
    delete d;
}

void FilterStream::reload()
{
    if (isLoading())
        abort();
    if (track().isEmpty()) return;
    AbstractStatusesModel::reload();
}

void FilterStream::parseDone(const QVariant &result)
{
//    DEBUG() << result;
    switch (result.type()) {
    case QVariant::Map: {
        QVariantMap object = result.toMap();
        if (object.keys().contains("text")) {
            addData(Status::parse(object));
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

const QString &FilterStream::delimited() const
{
    return d->delimited;
}

void FilterStream::setDelimited(const QString &delimited)
{
    if (d->delimited == delimited) return;
    d->delimited = delimited;
    emit delimitedChanged(delimited);
}

const QString &FilterStream::follow() const
{
    return d->follow;
}

void FilterStream::setFollow(const QString &follow)
{
    if (d->follow == follow) return;
    d->follow = follow;
    emit followChanged(follow);
}

const QString &FilterStream::track() const
{
    return d->track;
}

void FilterStream::setTrack(const QString &track)
{
    if (d->track == track) return;
    d->track = track;
    emit trackChanged(track);
}
