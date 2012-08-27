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

#include "configuration.h"

class Configuration::Private
{
public:
    Private();
    QString charactersReservedPerMedia;
    QVariantList nonUsernamePaths;
    int maxMediaPerUpload;
    int photoSizeLimit;
    int shortUrlLength;
    int shortUrlLengthHttps;
};

Configuration::Private::Private()
    : maxMediaPerUpload(0)
    , photoSizeLimit(0)
    , shortUrlLength(0)
    , shortUrlLengthHttps(0)
{
}

Configuration::Configuration(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

Configuration::~Configuration()
{
    delete d;
}

const QString &Configuration::charactersReservedPerMedia() const
{
    return d->charactersReservedPerMedia;
}

void Configuration::setCharactersReservedPerMedia(const QString &charactersReservedPerMedia)
{
    if (d->charactersReservedPerMedia == charactersReservedPerMedia) return;
    d->charactersReservedPerMedia = charactersReservedPerMedia;
    emit charactersReservedPerMediaChanged(charactersReservedPerMedia);
}

const QVariantList &Configuration::nonUsernamePaths() const
{
    return d->nonUsernamePaths;
}

void Configuration::setNonUsernamePath(const QVariantList &nonUsernamePaths)
{
    if (d->nonUsernamePaths == nonUsernamePaths) return;
    d->nonUsernamePaths = nonUsernamePaths;
    emit nonUsernamePathsChanged(nonUsernamePaths);
}

int Configuration::maxMediaPerUpload() const
{
    return d->maxMediaPerUpload;
}

void Configuration::setMaxMediaPerUpload(int maxMediaPerUpload)
{
    if (d->maxMediaPerUpload == maxMediaPerUpload) return;
    d->maxMediaPerUpload = maxMediaPerUpload;
    emit maxMediaPerUploadChanged(maxMediaPerUpload);
}

int Configuration::photoSizeLimit() const
{
    return d->photoSizeLimit;
}

void Configuration::setPhotoSizeLimit(int photoSizeLimit)
{
    if (d->photoSizeLimit == photoSizeLimit) return;
    d->photoSizeLimit = photoSizeLimit;
    emit photoSizeLimitChanged(photoSizeLimit);
}

int Configuration::shortUrlLength() const
{
    return d->shortUrlLength;
}

void Configuration::setShortUrlLength(int shortUrlLength)
{
    if (d->shortUrlLength == shortUrlLength) return;
    d->shortUrlLength = shortUrlLength;
    emit shortUrlLengthChanged(shortUrlLength);
}

int Configuration::shortUrlLengthHttps() const
{
    return d->shortUrlLengthHttps;
}

void Configuration::setShortUrlLengthHttps(int shortUrlLengthHttps)
{
    if (d->shortUrlLengthHttps == shortUrlLengthHttps) return;
    d->shortUrlLengthHttps = shortUrlLengthHttps;
    emit shortUrlLengthHttpsChanged(shortUrlLengthHttps);
}
