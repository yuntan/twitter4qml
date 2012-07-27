#include "activitysummary.h"
#include "twitter4qml.h"

class ActivitySummary::Private
{
public:
    QString id;
    QVariantList favoriters;
    QString favoritersCount;
    QVariantList repliers;
    QString repliersCount;
    QString retweetersCount;
    QVariantList retweeters;
};

ActivitySummary::ActivitySummary(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
    connect(this, SIGNAL(idChanged(QString)), this, SLOT(exec()));
}

ActivitySummary::~ActivitySummary()
{
    delete d;
}

void ActivitySummary::exec()
{
    if (id().isEmpty()) return;
    AbstractTwitterAction::exec();
}

const QString &ActivitySummary::id() const
{
    return d->id;
}

void ActivitySummary::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

const QVariantList &ActivitySummary::favoriters() const
{
    return d->favoriters;
}

void ActivitySummary::setFavoriters(const QVariantList &favoriters)
{
    if (d->favoriters == favoriters) return;
    d->favoriters = favoriters;
    emit favoritersChanged(favoriters);
}

const QString &ActivitySummary::favoritersCount() const
{
    return d->favoritersCount;
}

void ActivitySummary::setFavoritersCount(const QString &favoritersCount)
{
    if (d->favoritersCount == favoritersCount) return;
    d->favoritersCount = favoritersCount;
    emit favoritersCountChanged(favoritersCount);
}

const QVariantList &ActivitySummary::repliers() const
{
    return d->repliers;
}

void ActivitySummary::setRepliers(const QVariantList &repliers)
{
    if (d->repliers == repliers) return;
    d->repliers = repliers;
    emit repliersChanged(repliers);
}

const QString &ActivitySummary::repliersCount() const
{
    return d->repliersCount;
}

void ActivitySummary::setRepliersCount(const QString &repliersCount)
{
    if (d->repliersCount == repliersCount) return;
    d->repliersCount = repliersCount;
    emit repliersCountChanged(repliersCount);
}

const QString &ActivitySummary::retweetersCount() const
{
    return d->retweetersCount;
}

void ActivitySummary::setRetweetersCount(const QString &retweetersCount)
{
    if (d->retweetersCount == retweetersCount) return;
    d->retweetersCount = retweetersCount;
    emit retweetersCountChanged(retweetersCount);
}

const QVariantList &ActivitySummary::retweeters() const
{
    return d->retweeters;
}

void ActivitySummary::setRetweeters(const QVariantList &retweeters)
{
    if (d->retweeters == retweeters) return;
    d->retweeters = retweeters;
    emit retweetersChanged(retweeters);
}

