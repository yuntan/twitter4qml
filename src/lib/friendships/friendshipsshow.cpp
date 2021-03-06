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

#include "friendshipsshow.h"
#include <QtCore/QTimer>

class FriendshipsShow::Private : public QObject
{
    Q_OBJECT
public:
    Private(FriendshipsShow *parent);

private slots:
    void changed();

private:
    FriendshipsShow *q;
    QTimer timer;
};

FriendshipsShow::Private::Private(FriendshipsShow *parent)
    : QObject(parent)
    , q(parent)
{
    connect(q, SIGNAL(source_idChanged(QString)), this, SLOT(changed()));
    connect(q, SIGNAL(source_screen_nameChanged(QString)), this, SLOT(changed()));
    connect(q, SIGNAL(target_idChanged(QString)), this, SLOT(changed()));
    connect(q, SIGNAL(target_screen_nameChanged(QString)), this, SLOT(changed()));

    timer.setInterval(0);
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), q, SLOT(exec()));
}

void FriendshipsShow::Private::changed()
{
    if (timer.isActive()) return;
    q->relationship(QVariantMap());
    timer.start();
}

FriendshipsShow::FriendshipsShow(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private(this))
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

void FriendshipsShow::exec()
{
    if (source_id().isEmpty() && source_screen_name().isEmpty()) return;
    if (target_id().isEmpty() && target_screen_name().isEmpty()) return;
    AbstractTwitterAction::exec();
}

#include "friendshipsshow.moc"
