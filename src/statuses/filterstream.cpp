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
