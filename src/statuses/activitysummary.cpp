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

