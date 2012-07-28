#include "abstracttwitteraction.h"

#include "oauthmanager.h"
#include "jsonparser.h"

#include <QtCore/QMetaProperty>
#include <QtCore/QStringList>
#include <QtCore/QUrl>
#include <QtCore/qnumeric.h>
#include <QtNetwork/QNetworkReply>

class AbstractTwitterAction::Private : public QObject
{
    Q_OBJECT
public:
    Private(AbstractTwitterAction *parent);

    bool isLoading;
    QVariant data;

public slots:
    void exec();

private slots:
    void readData();
    void finished();
    void error(QNetworkReply::NetworkError error);
    void parsed(const QVariant &result);

private:
    AbstractTwitterAction *q;
    JSONParser parser;
    QByteArray buffer;
};

AbstractTwitterAction::Private::Private(AbstractTwitterAction *parent)
    : QObject(parent)
    , isLoading(false)
    , q(parent)
{
    connect(&parser, SIGNAL(parsed(QVariant)), this, SLOT(parsed(QVariant)));
}

void AbstractTwitterAction::Private::exec()
{
    if (isLoading) return;
    if (q->authenticationMethod() != AuthorizeByNothing && !OAuthManager::instance().isAuthorized()) return;

    QUrl url = q->api();
    QStringList body;

    QMultiMap<QString, QByteArray> params;
    const QMetaObject *mo = q->metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty prop = mo->property(i);
        if (!prop.isDesignable()) continue;
        const char *key = prop.name();
        QVariant value = q->property(key);
        if (key[0] == '_')
            key++;
        bool ok;
        switch (value.type()) {
        case QVariant::Bool:
            params.insert(key, value.toString().toAscii());
            url.addEncodedQueryItem(QString(key).toUtf8().toPercentEncoding(), value.toString().toUtf8().toPercentEncoding());
            body.append(QString("%1=%2").arg(key).arg(value.toString()));
            break;
        case QVariant::String:
            if (!value.toString().isNull()) {
                params.insert(key, value.toString().toUtf8());
                url.addEncodedQueryItem(QString(key).toUtf8().toPercentEncoding(), value.toString().toUtf8().toPercentEncoding());
                body.append(QString("%1=%2").arg(key).arg(value.toString()));
            }
            break;
        case QVariant::Double:
            if (!qFuzzyCompare(value.toDouble(&ok), 0.0) && ok && !qIsNaN(value.toDouble())) {
                QString val = QString::number(value.toDouble(), 'f');
                DEBUG() << key << value << value.toDouble() << QString::number(value.toDouble(), 'f') << val;
                params.insert(key, val.toAscii());
                url.addEncodedQueryItem(QString(key).toUtf8().toPercentEncoding(), val.toAscii().toPercentEncoding());
                body.append(QString("%1=%2").arg(key).arg(val));
            }
            break;
        case QVariant::Int:
            if (value.toInt() > 0) {
                params.insert(key, value.toString().toAscii());
                url.addEncodedQueryItem(QString(key).toUtf8().toPercentEncoding(), value.toString().toUtf8().toPercentEncoding());
                body.append(QString("%1=%2").arg(key).arg(value.toString()));
            }
            break;
        case QVariant::LongLong:
            if (value.toLongLong() > 0) {
                params.insert(key, value.toString().toAscii());
                url.addEncodedQueryItem(QString(key).toUtf8().toPercentEncoding(), value.toString().toUtf8().toPercentEncoding());
                body.append(QString("%1=%2").arg(key).arg(value.toString()));
            }
            break;
        case QVariant::List:
            if (!value.toList().isEmpty()) {
                foreach (const QVariant &val, value.toList()) {
                    params.insert(QString("%1[]").arg(key), val.toByteArray());
                }
            }
            break;
        default:
            DEBUG() << key << "not found" << value;
            break;
        }
    }

//    DEBUG() << url;
    QNetworkReply *reply = 0;
    switch (q->authenticationMethod()) {
    case AuthorizeByNothing:
        if (q->httpMethod() == QLatin1String("GET")) {
            QNetworkRequest request(url);
            request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
            request.setRawHeader("User-Agent", "Twitter4QML");
            reply = OAuthManager::instance().networkAccessManager()->get(request);
        } else if (q->httpMethod() == QLatin1String("POST")) {
            QNetworkRequest request(q->api());
            request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
            request.setRawHeader("User-Agent", "Twitter4QML");
            reply = OAuthManager::instance().networkAccessManager()->post(request, body.join("&").toUtf8());
        }
        break;
    case AuthorizeByHeader:
        OAuthManager::instance().setAuthorizeBy(OAuthManager::AuthorizeByHeader);
        reply = OAuthManager::instance().request(q->httpMethod(), q->api(), params, q->isMultiPart());
        break;
    case AuthorizeByBody:
        OAuthManager::instance().setAuthorizeBy(OAuthManager::AuthorizeByBody);
        reply = OAuthManager::instance().request(q->httpMethod(), q->api(), params, q->isMultiPart());
        break;
    case AuthorizeByUrl:
        OAuthManager::instance().setAuthorizeBy(OAuthManager::AuthorizeByUrl);
        reply = OAuthManager::instance().request(q->httpMethod(), q->api(), params, q->isMultiPart());
        break;
    }

    if (reply) {
        buffer.clear();
        connect(reply, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(reply, SIGNAL(finished()), this, SLOT(finished()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));

        q->setLoading(true);
    }
//    DEBUG() << reply->url();
}

void AbstractTwitterAction::Private::readData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;
    buffer.append(reply->readAll());
}

void AbstractTwitterAction::Private::finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;
//    DEBUG() << reply->url() << buffer;
    parser.parse(buffer);
    reply->deleteLater();
}

void AbstractTwitterAction::Private::error(QNetworkReply::NetworkError error)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    DEBUG() << error << reply->errorString() << reply->url();
    QVariantMap data;
    data.insert("error", reply->errorString());
    q->setData(data);
    reply->deleteLater();
    q->setLoading(false);
}

void AbstractTwitterAction::Private::parsed(const QVariant &result)
{
//    DEBUG() << q->metaObject()->className() << result;
    if (result.type() == QVariant::Map) {
        q->setParameters(result.toMap());
    }
    q->setData(result);
    q->setLoading(false);
}

AbstractTwitterAction::AbstractTwitterAction(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

void AbstractTwitterAction::setParameters(const QVariantMap &parameters)
{
    const QMetaObject *mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty prop = mo->property(i);
        if (!prop.isUser()) continue;
        const char *key = prop.name();
        if (parameters.contains(key)) {
            if (!setProperty(key, parameters.value(key))) {
                DEBUG() << mo->className() << key << parameters.value(key);
            }
        }
    }
}

bool AbstractTwitterAction::isLoading() const
{
    return d->isLoading;
}

void AbstractTwitterAction::setLoading(bool isLoading)
{
    if (d->isLoading == isLoading) return;
    d->isLoading = isLoading;
    emit loadingChanged(isLoading);
}

const QVariant &AbstractTwitterAction::data() const
{
    return d->data;
}

void AbstractTwitterAction::setData(const QVariant &data)
{
    if (d->data == data) return;
    d->data = data;
    emit dataChanged(data);
}

void AbstractTwitterAction::exec()
{
    d->exec();
}

#include "abstracttwitteraction.moc"