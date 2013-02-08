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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../tools/abstracttwitteraction.h"

class Configuration : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString characters_reserved_per_media READ characters_reserved_per_media WRITE characters_reserved_per_media NOTIFY characters_reserved_per_mediaChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantList non_username_paths READ non_username_paths WRITE non_username_paths NOTIFY non_username_pathsChanged DESIGNABLE false USER true)
    Q_PROPERTY(int max_media_per_upload READ max_media_per_upload WRITE max_media_per_upload NOTIFY max_media_per_uploadChanged DESIGNABLE false USER true)
    Q_PROPERTY(int photo_size_limit READ photo_size_limit WRITE photo_size_limit NOTIFY photo_size_limitChanged DESIGNABLE false USER true)
    Q_PROPERTY(int short_url_length READ short_url_length WRITE short_url_length NOTIFY short_url_lengthChanged DESIGNABLE false USER true)
    Q_PROPERTY(int short_url_length_https READ short_url_length_https WRITE short_url_length_https NOTIFY short_url_length_httpsChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantMap photo_sizes READ photo_sizes WRITE photo_sizes NOTIFY photo_sizesChanged DESIGNABLE false USER true)
public:
    explicit Configuration(QObject *parent = 0);

signals:
    void characters_reserved_per_mediaChanged(const QString &characters_reserved_per_media);
    void non_username_pathsChanged(const QVariantList &non_username_paths);
    void max_media_per_uploadChanged(int max_media_per_upload);
    void photo_size_limitChanged(int photo_size_limit);
    void short_url_lengthChanged(int short_url_length);
    void short_url_length_httpsChanged(int short_url_length_https);
    void photo_sizesChanged(const QVariantMap &photo_sizes);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/help/configuration.json"); }

private:
    ADD_PROPERTY(const QString &, characters_reserved_per_media, QString)
    ADD_PROPERTY(const QVariantList &, non_username_paths, QVariantList)
    ADD_PROPERTY(int, max_media_per_upload, int)
    ADD_PROPERTY(int, photo_size_limit, int)
    ADD_PROPERTY(int, short_url_length, int)
    ADD_PROPERTY(int, short_url_length_https, int)
    ADD_PROPERTY(const QVariantMap &, photo_sizes, QVariantMap)
};

#endif // CONFIGURATION_H
