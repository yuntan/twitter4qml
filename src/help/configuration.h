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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../tools/abstracttwitteraction.h"

class Configuration : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString characters_reserved_per_media READ charactersReservedPerMedia WRITE setCharactersReservedPerMedia NOTIFY charactersReservedPerMediaChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantList non_username_paths READ nonUsernamePaths WRITE setNonUsernamePath NOTIFY nonUsernamePathsChanged DESIGNABLE false USER true)
    Q_PROPERTY(int max_media_per_upload READ maxMediaPerUpload WRITE setMaxMediaPerUpload NOTIFY maxMediaPerUploadChanged DESIGNABLE false USER true)
    Q_PROPERTY(int photo_size_limit READ photoSizeLimit WRITE setPhotoSizeLimit NOTIFY photoSizeLimitChanged DESIGNABLE false USER true)
    Q_PROPERTY(int short_url_length READ shortUrlLength WRITE setShortUrlLength NOTIFY shortUrlLengthChanged DESIGNABLE false USER true)
    Q_PROPERTY(int short_url_length_https READ shortUrlLengthHttps WRITE setShortUrlLengthHttps NOTIFY shortUrlLengthHttpsChanged DESIGNABLE false USER true)
public:
    explicit Configuration(QObject *parent = 0);
    ~Configuration();

    const QString &charactersReservedPerMedia() const;
    void setCharactersReservedPerMedia(const QString &charactersReservedPerMedia);
    const QVariantList &nonUsernamePaths() const;
    void setNonUsernamePath(const QVariantList &nonUsernamePaths);
    int maxMediaPerUpload() const;
    void setMaxMediaPerUpload(int maxMediaPerUpload);
    int photoSizeLimit() const;
    void setPhotoSizeLimit(int photoSizeLimit);
    int shortUrlLength() const;
    void setShortUrlLength(int shortUrlLength);
    int shortUrlLengthHttps() const;
    void setShortUrlLengthHttps(int shortUrlLengthHttps);

signals:
    void charactersReservedPerMediaChanged(const QString &charactersReservedPerMedia);
    void nonUsernamePathsChanged(const QVariantList &nonUsernamePaths);
    void maxMediaPerUploadChanged(int maxMediaPerUpload);
    void photoSizeLimitChanged(int photoSizeLimit);
    void shortUrlLengthChanged(int shortUrlLength);
    void shortUrlLengthHttpsChanged(int shortUrlLengthHttps);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("http://api.twitter.com/1/help/configuration.json"); }

private:
    class Private;
    Private *d;
};

#endif // CONFIGURATION_H
