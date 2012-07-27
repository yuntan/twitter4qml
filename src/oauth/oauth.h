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
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
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

    const QString &userId() const;
    void setUserId(const QString &userId);

    const QString &screenName() const;
    void setScreenName(const QString &screenName);

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
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);

private:
    class Private;
    Private *d;
};

#endif // OAUTH_H
