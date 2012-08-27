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

#include "abstractlistaction.h"

class AbstractListAction::Private
{
public:
    QString listId;
    QString description;
    QString mode;
    QString name;
};

AbstractListAction::AbstractListAction(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

AbstractListAction::~AbstractListAction()
{
    delete d;
}

const QString &AbstractListAction::listId() const
{
    return d->listId;
}

void AbstractListAction::setListId(const QString &listId)
{
    if (d->listId == listId) return;
    d->listId = listId;
    emit listIdChanged(listId);
}

const QString &AbstractListAction::description() const
{
    return d->description;
}

void AbstractListAction::setDescription(const QString &description)
{
    if (d->description == description) return;
    d->description = description;
    emit descriptionChanged(description);
}

const QString &AbstractListAction::mode() const
{
    return d->mode;
}

void AbstractListAction::setMode(const QString &mode)
{
    if (d->mode == mode) return;
    d->mode = mode;
    emit modeChanged(mode);
}

const QString &AbstractListAction::name() const
{
    return d->name;
}

void AbstractListAction::setName(const QString &name)
{
    if (d->name == name) return;
    d->name = name;
    emit nameChanged(name);
}

