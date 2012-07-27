#ifndef OAUTHMANAGER_H
#define OAUTHMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QMultiMap>
#include <QtCore/QUrl>

#include "twitter4qml_global.h"

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class OAuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString consumerKey READ consumerKey WRITE setConsumerKey NOTIFY consumerKeyChanged)
    Q_PROPERTY(QString consumerSecret READ consumerSecret WRITE setConsumerSecret NOTIFY consumerSecretChanged)
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(QString tokenSecret READ tokenSecret WRITE setTokenSecret NOTIFY tokenSecretChanged)
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
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
    const QString &userId() const;
    const QString &screenName() const;
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
    void setUserId(const QString &userId);
    void setScreenName(const QString &screenName);
    void setAuthorized(bool isAuthorized);

signals:
    void networkAccessManagerChanged(QNetworkAccessManager *networkAccessManager);
    void consumerKeyChanged(const QString &consumerKey);
    void consumerSecretChanged(const QString &consumerSecret);
    void tokenChanged(const QString &token);
    void tokenSecretChanged(const QString &tokenSecret);
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void authorizedChanged(bool isAuthorized);

private:
    explicit OAuthManager(QObject *parent = 0);
    class Private;
    Private *d;
};

#endif // OAUTHMANAGER_H
