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

#include "oauth.h"
#include "oauthmanager.h"

#include <QtGui/QDesktopServices>
#include <QtNetwork/QNetworkReply>

const char* const request_token_url = "https://api.twitter.com/oauth/request_token";
const char* const authorize_url = "https://api.twitter.com/oauth/authorize?oauth_token=%1";
const char* const access_token_url = "https://api.twitter.com/oauth/access_token";

class OAuth::Private : public QObject
{
    Q_OBJECT
public:
    Private(OAuth *parent);

    void setState(State state);
    State state;

private slots:
    void updateStatus();
    void finished();
    void error(QNetworkReply::NetworkError networkError);

private:
    OAuth *q;
};

OAuth::Private::Private(OAuth *parent)
    : QObject(parent)
    , state(Unauthorized)
    , q(parent)
{
    connect(&OAuthManager::instance(), SIGNAL(consumerKeyChanged(QString)), q, SIGNAL(consumerKeyChanged(QString)));
    connect(&OAuthManager::instance(), SIGNAL(consumerSecretChanged(QString)), q, SIGNAL(consumerSecretChanged(QString)));
    connect(&OAuthManager::instance(), SIGNAL(tokenChanged(QString)), q, SIGNAL(tokenChanged(QString)));
    connect(&OAuthManager::instance(), SIGNAL(tokenSecretChanged(QString)), q, SIGNAL(tokenSecretChanged(QString)));
    connect(&OAuthManager::instance(), SIGNAL(user_idChanged(QString)), q, SIGNAL(user_idChanged(QString)));
    connect(&OAuthManager::instance(), SIGNAL(screen_nameChanged(QString)), q, SIGNAL(screen_nameChanged(QString)));

    connect(q, SIGNAL(tokenChanged(QString)), this, SLOT(updateStatus()));
    connect(q, SIGNAL(tokenSecretChanged(QString)), this, SLOT(updateStatus()));
    connect(q, SIGNAL(user_idChanged(QString)), this, SLOT(updateStatus()));
    connect(q, SIGNAL(screen_nameChanged(QString)), this, SLOT(updateStatus()));
    updateStatus();
}

void OAuth::Private::setState(State s)
{
    if (state == s) return;
    state = s;
    emit q->stateChanged(state);
    OAuthManager::instance().setAuthorized(state == Authorized);
}

void OAuth::Private::updateStatus()
{
    if (state == Unauthorized
            && !OAuthManager::instance().token().isEmpty()
            && !OAuthManager::instance().tokenSecret().isEmpty()
            ) {
        setState(Authorized);
    }
}

void OAuth::Private::finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    switch (state) {
    case ObtainUnauthorizedRequestToken:
        if (reply->url() == QUrl(request_token_url)) {
            if (OAuthManager::instance().updateToken(reply)) {
                setState(RequestTokenReceived);
            } else {
                q->unauthorize();
            }
        }
        break;
    case ExchangeRequestTokenForAccessToken:
        if (reply->url() == QUrl(access_token_url)) {
            if (OAuthManager::instance().updateToken(reply)) {
                setState(Authorized);
            } else {
                q->unauthorize();
            }
        }
        break;
    default:
        qWarning() << "got reply in state" << state;
        break;
    }
    reply->deleteLater();
}

void OAuth::Private::error(QNetworkReply::NetworkError networkError)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;
    DEBUG() << networkError << reply->url() << reply->errorString();
    reply->deleteLater();
}

OAuth::OAuth(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

OAuth::State OAuth::state() const
{
    return d->state;
}

const QString &OAuth::consumerKey() const
{
    return OAuthManager::instance().consumerKey();
}

void OAuth::setConsumerKey(const QString &consumerKey)
{
    OAuthManager::instance().setConsumerKey(consumerKey);
}

const QString &OAuth::consumerSecret() const
{
    return OAuthManager::instance().consumerSecret();
}

void OAuth::setConsumerSecret(const QString &consumerSecret)
{
    OAuthManager::instance().setConsumerSecret(consumerSecret);
}

const QString &OAuth::token() const
{
    return OAuthManager::instance().token();
}

void OAuth::setToken(const QString &token)
{
    OAuthManager::instance().setToken(token);
}

const QString &OAuth::tokenSecret() const
{
    return OAuthManager::instance().tokenSecret();
}

void OAuth::setTokenSecret(const QString &tokenSecret)
{
    OAuthManager::instance().setTokenSecret(tokenSecret);
}

const QString &OAuth::user_id() const
{
    return OAuthManager::instance().user_id();
}

void OAuth::user_id(const QString &user_id)
{
    OAuthManager::instance().user_id(user_id);
}

const QString &OAuth::screen_name() const
{
    return OAuthManager::instance().screen_name();
}

void OAuth::screen_name(const QString &screen_name)
{
    OAuthManager::instance().screen_name(screen_name);
}

void OAuth::request_token(const QString &callback)
{
    if (state() != Unauthorized) {
        qWarning() << "state =" << (int)state();
        return;
    }
    QMultiMap<QString, QByteArray> params;
    if (!callback.isNull())
        params.insert(QLatin1String("oauth_callback"), callback.toUtf8());
    OAuthManager::instance().setAuthorizeBy(OAuthManager::AuthorizeByHeader);
    QNetworkReply *reply = OAuthManager::instance().request(QLatin1String("POST"), QUrl(request_token_url), params);
    connect(reply, SIGNAL(finished()), d, SLOT(finished()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), d, SLOT(error(QNetworkReply::NetworkError)));
    d->setState(ObtainUnauthorizedRequestToken);
}

void OAuth::authorize()
{
    if (state() != RequestTokenReceived) {
        qWarning() << "state =" << state();
        return;
    }
    QDesktopServices::openUrl(QUrl(QString(authorize_url).arg(OAuthManager::instance().token())));
    d->setState(UserAuthorizesRequestToken);
}

void OAuth::access_token(const QString &pin)
{
    if (state() != UserAuthorizesRequestToken) {
        qWarning() << "state =" << state();
        return;
    }
    QMultiMap<QString, QByteArray> params;
    params.insert(QLatin1String("oauth_verifier"), pin.toUtf8());
    OAuthManager::instance().setAuthorizeBy(OAuthManager::AuthorizeByHeader);
    QNetworkReply *reply = OAuthManager::instance().request(QLatin1String("POST"), QUrl(access_token_url), params);
    connect(reply, SIGNAL(finished()), d, SLOT(finished()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), d, SLOT(error(QNetworkReply::NetworkError)));
    d->setState(ExchangeRequestTokenForAccessToken);
}

void OAuth::unauthorize()
{
    DEBUG();
    OAuthManager::instance().setToken(QString());
    OAuthManager::instance().setTokenSecret(QString());
    OAuthManager::instance().user_id(QString());
    OAuthManager::instance().screen_name(QString());
    d->setState(Unauthorized);
    DEBUG();
}

#include "oauth.moc"
