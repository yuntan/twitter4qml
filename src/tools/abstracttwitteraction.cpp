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
    if (!OAuthManager::instance().isAuthorized()) return;

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
            params.insert(key, value.toString().toUtf8());
            body.append(QString("%1=%2").arg(key).arg(value.toString()));
            break;
        case QVariant::String:
            if (!value.toString().isNull()) {
                params.insert(key, value.toString().toUtf8());
                body.append(QString("%1=%2").arg(key).arg(value.toString()));
            }
            break;
        case QVariant::Double:
            if (!qFuzzyCompare(value.toDouble(&ok), 0.0) && ok && !qIsNaN(value.toDouble())) {
                QString val = QString::number(value.toDouble(), 'f');
                params.insert(key, val.toUtf8());
                body.append(QString("%1=%2").arg(key).arg(val));
            }
            break;
        case QVariant::Int:
            if (value.toInt() > 0) {
                params.insert(key, value.toString().toUtf8());
                body.append(QString("%1=%2").arg(key).arg(value.toString()));
            }
            break;
        case QVariant::LongLong:
            if (value.toLongLong() > 0) {
                params.insert(key, value.toString().toUtf8());
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

    QNetworkReply *reply = 0;
    switch (q->authenticationMethod()) {
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
