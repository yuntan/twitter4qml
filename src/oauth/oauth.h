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

#ifndef OAUTH_H
#define OAUTH_H

#include <QObject>

class OAuth : public QObject
{
    Q_OBJECT
    Q_ENUMS(State)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString consumer_key READ consumerKey WRITE setConsumerKey NOTIFY consumerKeyChanged)
    Q_PROPERTY(QString consumer_secret READ consumerSecret WRITE setConsumerSecret NOTIFY consumerSecretChanged)
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(QString token_secret READ tokenSecret WRITE setTokenSecret NOTIFY tokenSecretChanged)
    Q_PROPERTY(QString user_id READ user_id WRITE user_id NOTIFY user_idChanged)
    Q_PROPERTY(QString screen_name READ screen_name WRITE screen_name NOTIFY screen_nameChanged)
public:
    enum State {
        Unauthorized,
        ObtainUnauthorizedRequestToken,
        RequestTokenReceived,
        UserAuthorizesRequestToken,
        ExchangeRequestTokenForAccessToken,
        Authorized
    };

    explicit OAuth(QObject *parent = 0);
    
    State state() const;
    const QString &consumerKey() const;
    void setConsumerKey(const QString &consumerKey);

    const QString &consumerSecret() const;
    void setConsumerSecret(const QString &consumerSecret);

    const QString &token() const;
    void setToken(const QString &token);

    const QString &tokenSecret() const;
    void setTokenSecret(const QString &tokenSecret);

    const QString &user_id() const;
    void user_id(const QString &user_id);

    const QString &screen_name() const;
    void screen_name(const QString &screen_name);

public slots:
    void request_token(const QString &callback = QString());
    void authorize();
    void access_token(const QString &pin);
    void unauthorize();

signals:
    void stateChanged(OAuth::State state);
    void consumerKeyChanged(const QString &consumerKey);
    void consumerSecretChanged(const QString &consumerSecret);
    void tokenChanged(const QString &token);
    void tokenSecretChanged(const QString &tokenSecret);
    void user_idChanged(const QString &user_id);
    void screen_nameChanged(const QString &screen_name);

private:
    class Private;
    Private *d;
};

#endif // OAUTH_H
