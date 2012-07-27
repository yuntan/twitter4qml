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
