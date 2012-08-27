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

#include "showfriendships.h"
#include <QtCore/QTimer>

class ShowFriendships::Private : public QObject
{
    Q_OBJECT
public:
    Private(ShowFriendships *parent);

    QString sourceId;
    QString sourceScreenName;
    QString targetId;
    QString targetScreenName;
    QVariantMap relationship;

private slots:
    void changed();

private:
    ShowFriendships *q;
    QTimer timer;
};

ShowFriendships::Private::Private(ShowFriendships *parent)
    : QObject(parent)
    , q(parent)
{
    connect(q, SIGNAL(sourceIdChanged(QString)), this, SLOT(changed()));
    connect(q, SIGNAL(sourceScreenNameChanged(QString)), this, SLOT(changed()));
    connect(q, SIGNAL(targetIdChanged(QString)), this, SLOT(changed()));
    connect(q, SIGNAL(targetScreenNameChanged(QString)), this, SLOT(changed()));

    timer.setInterval(0);
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), q, SLOT(exec()));
}

void ShowFriendships::Private::changed()
{
    if (timer.isActive()) return;
    q->setRelationship(QVariantMap());
    timer.start();
}

ShowFriendships::ShowFriendships(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private(this))
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

void ShowFriendships::exec()
{
    if (sourceId().isEmpty() && sourceScreenName().isEmpty()) return;
    if (targetId().isEmpty() && targetScreenName().isEmpty()) return;
    AbstractTwitterAction::exec();
}

const QString &ShowFriendships::sourceId() const
{
    return d->sourceId;
}

void ShowFriendships::setSourceId(const QString &sourceId)
{
    if (d->sourceId == sourceId) return;
    d->sourceId = sourceId;
    emit sourceIdChanged(sourceId);
}

const QString &ShowFriendships::sourceScreenName() const
{
    return d->sourceScreenName;
}

void ShowFriendships::setSourceScreenName(const QString &sourceScreenName)
{
    if (d->sourceScreenName == sourceScreenName) return;
    d->sourceScreenName = sourceScreenName;
    emit sourceScreenNameChanged(sourceScreenName);
}

const QString &ShowFriendships::targetId() const
{
    return d->targetId;
}

void ShowFriendships::setTargetId(const QString &targetId)
{
    if (d->targetId == targetId) return;
    d->targetId = targetId;
    emit targetIdChanged(targetId);
}

const QString &ShowFriendships::targetScreenName() const
{
    return d->targetScreenName;
}

void ShowFriendships::setTargetScreenName(const QString &targetScreenName)
{
    if (d->targetScreenName == targetScreenName) return;
    d->targetScreenName = targetScreenName;
    emit targetScreenNameChanged(targetScreenName);
}

const QVariantMap &ShowFriendships::relationship() const
{
    return d->relationship;
}

void ShowFriendships::setRelationship(const QVariantMap &relationship)
{
    if (d->relationship == relationship) return;
    d->relationship = relationship;
    emit relationshipChanged(relationship);
}

#include "showfriendships.moc"
