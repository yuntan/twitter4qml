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

#include "updateprofile.h"

class UpdateProfile::Private
{
public:
    Private();

    QString name;
    QString url;
    QString location;
    QString description;
    bool includeEntities;
    bool skipStatus;
};

UpdateProfile::Private::Private()
    : includeEntities(true)
    , skipStatus(false)
{
}

UpdateProfile::UpdateProfile(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

UpdateProfile::~UpdateProfile()
{
    delete d;
}

const QString &UpdateProfile::name() const
{
    return d->name;
}

void UpdateProfile::setName(const QString &name)
{
    if (d->name == name) return;
    d->name = name;
    emit nameChanged(name);
}

const QString &UpdateProfile::url() const
{
    return d->url;
}

void UpdateProfile::setUrl(const QString &url)
{
    if (d->url == url) return;
    d->url = url;
    emit urlChanged(url);
}

const QString &UpdateProfile::location() const
{
    return d->location;
}

void UpdateProfile::setLocation(const QString &location)
{
    if (d->location == location) return;
    d->location = location;
    emit locationChanged(location);
}

const QString &UpdateProfile::description() const
{
    return d->description;
}

void UpdateProfile::setDescription(const QString &description)
{
    if (d->description == description) return;
    d->description = description;
    emit descriptionChanged(description);
}

bool UpdateProfile::includeEntities() const
{
    return d->includeEntities;
}

void UpdateProfile::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}

bool UpdateProfile::skipStatus() const
{
    return d->skipStatus;
}

void UpdateProfile::setSkipStatus(bool skipStatus)
{
    if (d->skipStatus == skipStatus) return;
    d->skipStatus = skipStatus;
    emit skipStatusChanged(skipStatus);
}
