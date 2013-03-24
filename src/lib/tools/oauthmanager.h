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

#ifndef OAUTHMANAGER_H
#define OAUTHMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QMultiMap>
#include <QtCore/QUrl>

#include "twitter4qml_global.h"

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class TWITTER4QML_EXPORT OAuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString consumerKey READ consumerKey WRITE setConsumerKey NOTIFY consumerKeyChanged)
    Q_PROPERTY(QString consumerSecret READ consumerSecret WRITE setConsumerSecret NOTIFY consumerSecretChanged)
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(QString tokenSecret READ tokenSecret WRITE setTokenSecret NOTIFY tokenSecretChanged)
    Q_PROPERTY(QString user_id READ user_id WRITE user_id NOTIFY user_idChanged)
    Q_PROPERTY(QString screen_name READ screen_name WRITE screen_name NOTIFY screen_nameChanged)
public:
    enum AuthorizeBy {
        AuthorizeByHeader,
        AuthorizeByBody,
        AuthorizeByUrl
    };

    static OAuthManager &instance();

    QNetworkAccessManager *networkAccessManager() const;
    AuthorizeBy authorizeBy() const;

    const QString &consumerKey() const;
    const QString &consumerSecret() const;
    const QString &token() const;
    const QString &tokenSecret() const;
    const QString &user_id() const;
    const QString &screen_name() const;
    bool isAuthorized() const;

    QNetworkReply *request(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, bool multiPart = false);
    QNetworkReply *request(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, const QByteArray &acceptEncoding);
    QNetworkReply *echo(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, const QUrl& serviceProvider, const QUrl &realm, bool multiPart = false);

    bool updateToken(QNetworkReply *reply);

public slots:
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);
    void setAuthorizeBy(AuthorizeBy authorizeBy);
    void setConsumerKey(const QString &consumerKey);
    void setConsumerSecret(const QString &consumerSecret);
    void setToken(const QString &token);
    void setTokenSecret(const QString &tokenSecret);
    void user_id(const QString &user_id);
    void screen_name(const QString &screen_name);
    void setAuthorized(bool isAuthorized);

signals:
    void networkAccessManagerChanged(QNetworkAccessManager *networkAccessManager);
    void consumerKeyChanged(const QString &consumerKey);
    void consumerSecretChanged(const QString &consumerSecret);
    void tokenChanged(const QString &token);
    void tokenSecretChanged(const QString &tokenSecret);
    void user_idChanged(const QString &user_id);
    void screen_nameChanged(const QString &screen_name);
    void authorizedChanged(bool isAuthorized);

private:
    explicit OAuthManager(QObject *parent = 0);
    class Private;
    Private *d;
};

#endif // OAUTHMANAGER_H
