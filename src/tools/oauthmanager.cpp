#include "oauthmanager.h"
#include "hmac_sha1.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class OAuthManager::Private : public QObject {
    Q_OBJECT
public:
    Private(OAuthManager *parent);

    QNetworkReply *request(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, bool multiPart, const QByteArray &acceptEncoding = QByteArray());
    QNetworkReply *echo(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, const QUrl& serviceProvider, const QUrl &realm, bool multiPart = false);
    bool updateToken(QNetworkReply* rep);

    QMap<QString, QByteArray> requestParams;

    QNetworkAccessManager *networkAccessManager;
    AuthorizeBy authorizeBy;

    QString consumerKey;
    QString consumerSecret;
    QString token;
    QString tokenSecret;
    QString userId;
    QString screenName;
    bool isAuthorized;

private slots:
    void setToken(const QString &token);

private:
    OAuthManager *q;

    QByteArray parameterEncoding(const QString &str) const;
    QByteArray normalize(const QMultiMap<QString, QByteArray> &param) const;
    QByteArray signature(const QString &method, const QUrl &url, const QByteArray &params) const;
    QMultiMap<QString, QByteArray> signatureParams(const QMultiMap<QString, QByteArray> &params) const;
    QByteArray authHeader(const QMultiMap<QString, QByteArray> &params, const QUrl &realm = QUrl()) const;
    void getTokenCredential();
};

OAuthManager::Private::Private(OAuthManager *parent)
    : QObject(parent)
    , networkAccessManager(0)
    , authorizeBy(AuthorizeByHeader)
    , isAuthorized(false)
    , q(parent)
{
    connect(q, SIGNAL(tokenChanged(QString)), this, SLOT(setToken(QString)));
}

void OAuthManager::Private::setToken(const QString &token)
{
    if (token.isEmpty()) {
        requestParams.clear();
    } else if (!requestParams.isEmpty()){
        requestParams["oauth_token"] = token.toAscii();
    }
}


QNetworkReply *OAuthManager::Private::request(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, bool multiPart, const QByteArray &acceptEncoding)
{
//    DEBUG() << method << url << params << multiPart;
    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    request.setRawHeader("Accept-Encoding",acceptEncoding);

    QNetworkReply *ret = 0;

    QDateTime dt = QDateTime::currentDateTimeUtc();
    QString timestamp;
    QString nonce;
    timestamp.setNum(dt.toTime_t());
    nonce.setNum(dt.toMSecsSinceEpoch());

    if (requestParams.isEmpty()) {
        requestParams["oauth_version"] = "1.0";
        requestParams["oauth_signature_method"] = "HMAC-SHA1";
        requestParams["oauth_consumer_key"] = consumerKey.toAscii();
        if (!token.isEmpty())
            requestParams["oauth_token"] = token.toAscii();
    }
    requestParams["oauth_nonce"] = nonce.toAscii();
    requestParams["oauth_timestamp"] = timestamp.toAscii();
//    DEBUG() << url.host();
    if (url.host() == "upload.twitter.com") {
        requestParams["oauth_signature"] =  signature(method,
                                                      url,
                                                      normalize(signatureParams(QMultiMap<QString, QByteArray>())));
    } else {
        requestParams["oauth_signature"] =  signature(method,
                                                      url,
                                                      normalize(signatureParams(params)));
    }
    if (method == "POST") {
        switch (authorizeBy) {
        case AuthorizeByHeader:
            DEBUG() << url;
            if (multiPart) {
                request.setRawHeader("Authorization", authHeader(QMultiMap<QString, QByteArray>()));
                request.setUrl(url);
                QString boundary = QString("--------------------") + nonce;
                QByteArray body;
                QList<QString> keys = params.keys();
                foreach(const QString &key, keys) {
                    QList<QByteArray> vals = params.values(key);
                    foreach(const QByteArray &val, vals) {
                        body.append(QString("--%1\r\n").arg(boundary).toAscii());
                        if (key == "media[]") {
                            QUrl url(val);
                            QFileInfo info(url.path());
                            QFile file(info.filePath());
                            body.append(QString("Content-Disposition: form-data; name=\"%1\"; filename=\"%2\"\r\n").arg(key).arg(info.fileName()).toUtf8());
                            body.append("Content-Type: image/jpeg\r\n");
//                            body.append("Content-Transfer-Encoding: binary\r\n");
                            body.append("\r\n");
                            if (file.open(QFile::ReadOnly)) {
                                body.append(file.readAll());
                                file.close();
                            } else {
                                DEBUG() << file.errorString();
                            }
                            body.append("\r\n");
                        } else {
                            body.append(QString("Content-Disposition: form-data; name=\"%1\"\r\n").arg(key).toAscii());
                            body.append("\r\n");
                            body.append(val);
                            body.append("\r\n");
                        }
                        DEBUG() << key << val << body.size();
                    }
                }
                body.append(QString("\r\n--%1--\r\n").arg(boundary).toAscii());
                DEBUG() << body.data();
                request.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(body.length()).toAscii());
                request.setHeader(QNetworkRequest::ContentTypeHeader, QString("multipart/form-data; boundary=%1").arg(boundary).toAscii());

                foreach (const QByteArray &rawHeader, request.rawHeaderList()) {
                    DEBUG() << rawHeader << request.rawHeader(rawHeader);
                }

                ret = q->networkAccessManager()->post(request, body);
            } else {
                request.setRawHeader("Authorization", authHeader(params));
                request.setUrl(url);
                ret = q->networkAccessManager()->post(request, normalize(QMultiMap<QString, QByteArray>()));
            }
            break;
        case AuthorizeByBody: {
            QUrl qurl(url);
            QList<QString> keys = requestParams.keys();
            foreach(const QString &key, keys) {
                QList<QByteArray> vals = requestParams.values(key);
                foreach(const QByteArray &val, vals) {
                    qurl.addEncodedQueryItem(parameterEncoding(key), val.toPercentEncoding());
                }
            }
            request.setUrl(qurl);
            ret = q->networkAccessManager()->post(request, normalize(params));
            DEBUG() << qurl << normalize(params);
            break;
        }
        case AuthorizeByUrl: {
            QMultiMap<QString, QByteArray> allParams(requestParams);
            allParams += params;
            QUrl qurl(url);
            QList<QString> keys = allParams.keys();
            foreach(const QString &key, keys) {
                QList<QByteArray> vals = allParams.values(key);
                foreach(const QByteArray &val, vals) {
                    qurl.addEncodedQueryItem(parameterEncoding(key), val.toPercentEncoding());
                }
            }
            request.setUrl(qurl);
            ret = q->networkAccessManager()->post(request, QByteArray());
            break;
        }
        }

    } else if (method == "GET") {
        switch (authorizeBy) {
        case AuthorizeByHeader:
            request.setRawHeader("Authorization", authHeader(params));
            request.setUrl(url);
            ret = q->networkAccessManager()->get(request);
            break;
        case AuthorizeByBody:
            qWarning() << "GET doesn't support AuthorizeByBody.";
            break;
        case AuthorizeByUrl: {
            QMultiMap<QString, QByteArray> allParams(requestParams);
            allParams += params;
            QUrl qurl(url);
            QList<QString> keys = allParams.keys();
            foreach(const QString &key, keys) {
                QList<QByteArray> vals = allParams.values(key);
                foreach(const QByteArray &val, vals) {
                    qurl.addEncodedQueryItem(parameterEncoding(key), val.toPercentEncoding());
                }
            }
            request.setUrl(qurl);
            ret = q->networkAccessManager()->get(request);
            break;
        }
        }
    }
//    DEBUG() << ret->url();
    return ret;
}

QNetworkReply *OAuthManager::Private::echo(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, const QUrl& serviceProvider, const QUrl &realm, bool multiPart)
{
    QNetworkRequest request;
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);

    QNetworkReply *ret = 0;

    QDateTime dt = QDateTime::currentDateTimeUtc();
    QString timestamp;
    QString nonce;
    timestamp.setNum(dt.toTime_t());
    nonce.setNum(dt.toMSecsSinceEpoch());

    if (requestParams.isEmpty()) {
        requestParams["oauth_version"] = "1.0";
        requestParams["oauth_signature_method"] = "HMAC-SHA1";
        requestParams["oauth_consumer_key"] = consumerKey.toAscii();
        if (!token.isEmpty())
            requestParams["oauth_token"] = token.toAscii();
    }
    requestParams["oauth_nonce"] = nonce.toAscii();
    requestParams["oauth_timestamp"] = timestamp.toAscii();

    requestParams["oauth_signature"] = signature("GET",
                                                  serviceProvider,
                                                  normalize(signatureParams(QMultiMap<QString, QByteArray>())));

    if (method == "POST") {
        switch (authorizeBy) {
        case AuthorizeByHeader:
//            DEBUG() << url;
            if (multiPart) {
                request.setRawHeader("X-Auth-Service-Provider", serviceProvider.toString().toUtf8());
                request.setRawHeader("X-Verify-Credentials-Authorization", authHeader(QMultiMap<QString, QByteArray>(), realm));
                request.setUrl(url);
                QString boundary = QString("--------------------") + nonce;
                QByteArray body;
                QList<QString> keys = params.keys();
                foreach(const QString &key, keys) {
                    QList<QByteArray> vals = params.values(key);
                    foreach(const QByteArray &val, vals) {
                        body.append(QString("--%1\r\n").arg(boundary).toAscii());
                        if (key == "media") {
                            QUrl url(val);
                            QFileInfo info(url.path());
                            QFile file(info.filePath());
                            body.append(QString("Content-Disposition: file; name=\"%1\"; filename=\"%2\"\r\n").arg(key).arg(info.fileName()).toUtf8());
                            body.append("Content-Type: application/octetstream\r\n");
//                            body.append("Content-Transfer-Encoding: binary\r\n");
                            body.append("\r\n");
                            if (file.open(QFile::ReadOnly)) {
                                body.append(file.readAll());
                                file.close();
                            } else {
                                DEBUG() << file.fileName() << file.errorString();
                            }
                            body.append("\r\n");
                        } else {
                            body.append(QString("Content-Disposition: form-data; name=\"%1\"\r\n").arg(key).toAscii());
                            body.append("\r\n");
                            body.append(val);
                            body.append("\r\n");
                        }
//                        DEBUG() << key << val << body.size();
                    }
                }
                body.append(QString("\r\n--%1--\r\n").arg(boundary).toAscii());
//                DEBUG() << body.data();
                request.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(body.length()).toAscii());
                request.setHeader(QNetworkRequest::ContentTypeHeader, QString("multipart/form-data; boundary=%1").arg(boundary).toAscii());

//                foreach (const QByteArray &rawHeader, request.rawHeaderList()) {
//                    DEBUG() << rawHeader << request.rawHeader(rawHeader);
//                }

                ret = q->networkAccessManager()->post(request, body);
            } else {
                request.setRawHeader("Authorization", authHeader(params));
                request.setUrl(url);
                ret = q->networkAccessManager()->post(request, normalize(QMultiMap<QString, QByteArray>()));
            }

            break;
        }
    } else if (method == "GET") {

    }
    return ret;
}

QByteArray OAuthManager::Private::parameterEncoding(const QString &str) const
{
    return str.toUtf8().toPercentEncoding();
}

QByteArray OAuthManager::Private::normalize(const QMultiMap<QString, QByteArray> &param) const
{
    QByteArray ret;
    QList<QString> keys = param.keys();
    foreach(const QString &key, keys) {
        QList<QByteArray> vals = param.values(key);
        foreach(const QByteArray &val, vals) {
            ret += parameterEncoding(key) + '=' + val.toPercentEncoding() + '&';
        }
    }
    ret.chop(1);
    return ret;
}

QByteArray OAuthManager::Private::signature(const QString &method, const QUrl &url, const QByteArray &params) const
{
    QByteArray key = parameterEncoding(consumerSecret) + "&" +
                     parameterEncoding(tokenSecret);
    QByteArray base = parameterEncoding(method) + "&" +
                      parameterEncoding(url.toString()) + "&" +
                      params.toPercentEncoding();
    return hmac_sha1(key,base).toBase64();
}

QMultiMap<QString, QByteArray> OAuthManager::Private::signatureParams(const QMultiMap<QString, QByteArray> &params) const
{
    QMultiMap<QString, QByteArray> ret(requestParams);
    ret.remove("oauth_signature");
    ret += params;
    return ret;
}

QByteArray OAuthManager::Private::authHeader(const QMultiMap<QString, QByteArray> &params, const QUrl &realm) const
{
    QByteArray ret = "OAuth ";
    if (realm.isValid()) {
        ret += "realm=\"" + realm.toString() + "\",";
    }
    QMultiMap<QString, QByteArray> map(requestParams);
    map += params;
    QMapIterator<QString, QByteArray> i(map);
    while (i.hasNext()) {
        i.next();
        ret += parameterEncoding(i.key());
        ret += "=";
        ret += '"';
        ret += i.value().toPercentEncoding();
        ret += '"';
        if (i.hasNext()) {
            ret += ",";
        }
    }
    return ret;
}

bool OAuthManager::Private::updateToken(QNetworkReply* reply)
{
    if (!reply) {
        return false;
    }
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "error : " << reply->errorString();
        return false;
    }
    QRegExp exp("(([^=&?]+)=([^=&?]+))(&([^=&?]+)=([^=&?]+))*");
    QByteArray result = reply->readAll();
    DEBUG() << result;
    if (!exp.exactMatch(result)) {
        return false;
    }
    QList<QByteArray> params = result.split('&');
    foreach (const QByteArray &param, params) {
        QList<QByteArray> tmp = param.split('=');
        QByteArray key = QByteArray::fromPercentEncoding(tmp.at(0));
        QByteArray val = QByteArray::fromPercentEncoding(tmp.at(1));
        DEBUG() << key << val;
        if (key == "oauth_token_secret") {
            q->setTokenSecret(val);
        } else if (key == "user_id") {
            q->setUserId(val);
        } else if (key == "screen_name") {
            q->setScreenName(val);
        } else {
            if (key == "oauth_token") {
                q->setToken(val);
            }
            requestParams[key] = val;
        }
    }
    return true;
}

OAuthManager &OAuthManager::instance()
{
    static OAuthManager ret;
    return ret;
}

OAuthManager::OAuthManager(QObject *parent)
    : QObject(parent)
{
    d = new Private(this);
}

QNetworkAccessManager *OAuthManager::networkAccessManager() const
{
    if (!d->networkAccessManager)
        d->networkAccessManager = new QNetworkAccessManager(d);
    return d->networkAccessManager;
}

void OAuthManager::setNetworkAccessManager(QNetworkAccessManager *networkAccessManager)
{
    if (d->networkAccessManager == networkAccessManager) return;
    d->networkAccessManager = networkAccessManager;
    emit networkAccessManagerChanged(networkAccessManager);
}

OAuthManager::AuthorizeBy OAuthManager::authorizeBy() const
{
    return d->authorizeBy;
}

void OAuthManager::setAuthorizeBy(AuthorizeBy authorizeBy)
{
    d->authorizeBy = authorizeBy;
}

const QString &OAuthManager::consumerKey() const
{
    return d->consumerKey;
}

void OAuthManager::setConsumerKey(const QString &consumerKey)
{
    if (d->consumerKey == consumerKey) return;
    d->consumerKey = consumerKey;
    emit consumerKeyChanged(consumerKey);
}

const QString &OAuthManager::consumerSecret() const
{
    return d->consumerSecret;
}

void OAuthManager::setConsumerSecret(const QString &consumerSecret)
{
    if (d->consumerSecret == consumerSecret) return;
    d->consumerSecret = consumerSecret;
    emit consumerSecretChanged(consumerSecret);
}

const QString &OAuthManager::token() const
{
    return d->token;
}

void OAuthManager::setToken(const QString &token)
{
    if (d->token == token) return;
    d->token = token;
    emit tokenChanged(token);
}

const QString &OAuthManager::tokenSecret() const
{
    return d->tokenSecret;
}

void OAuthManager::setTokenSecret(const QString &tokenSecret)
{
    if (d->tokenSecret == tokenSecret) return;
    d->tokenSecret = tokenSecret;
    emit tokenSecretChanged(tokenSecret);
}

const QString &OAuthManager::userId() const
{
    return d->userId;
}

void OAuthManager::setUserId(const QString &userId)
{
    if (d->userId == userId) return;
    d->userId = userId;
    emit userIdChanged(userId);
}

const QString &OAuthManager::screenName() const
{
    return d->screenName;
}

void OAuthManager::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

bool OAuthManager::isAuthorized() const
{
    return d->isAuthorized;
}

void OAuthManager::setAuthorized(bool isAuthorized)
{
    if (d->isAuthorized == isAuthorized) return;
    d->isAuthorized = isAuthorized;
    emit authorizedChanged(isAuthorized);
}

QNetworkReply *OAuthManager::request(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, bool multiPart)
{
    return d->request(method, url, params, multiPart);
}

QNetworkReply *OAuthManager::request(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, const QByteArray &acceptEncoding)
{
    return d->request(method, url, params, false, acceptEncoding);
}

QNetworkReply *OAuthManager::echo(const QString &method, const QUrl &url, const QMultiMap<QString, QByteArray> &params, const QUrl& serviceProvider, const QUrl &realm, bool multiPart)
{
    return d->echo(method, url, params, serviceProvider, realm, multiPart);
}

bool OAuthManager::updateToken(QNetworkReply *reply)
{
    return d->updateToken(reply);
}

#include "oauthmanager.moc"
