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

#include "abstracttwittermodel.h"
#include "oauthmanager.h"
#include "jsonparser.h"

#include <QtCore/QMetaProperty>
#include <QtCore/QPointer>
#include <QtCore/QStack>
#include <QtCore/QStringList>
#include <QtCore/QTimer>
#include <QtCore/QUrl>
#if QT_VERSION >= 0x050000
#include <QtCore/QUrlQuery>
#endif
#include <QtCore/qnumeric.h>

#include <QtNetwork/QNetworkReply>

class AbstractTwitterModel::Private : public QObject
{
    Q_OBJECT
public:
    enum Action {
        Add,
        Remove,
        Update
    };
    Private(AbstractTwitterModel *parent);

    bool enabled;
    bool isLoading;
    PushOrder pushOrder;
    QStringList ids;
    QList< QPair<Private::Action, QVariant> > stack;
    QString sortKey;
    QString cacheKey;
    QList<QObject *> childObjects;
    QTimer timer;
    bool filtering;

    int xrlLimit;
    int xrlRemaining;
    QDateTime xrlReset;

#if QT_VERSION >= 0x050000
    QHash<int, QByteArray> roleNames;
#endif

public slots:
    void reload();
    void abort();
    void reset();

private slots:
    void enabledChanged(bool enabled);
    void authorizedChanged(bool isAuthorized);
    void readData();
    void finished();
    void error(QNetworkReply::NetworkError error);
    void parsed(const QVariant &result);
    void timeout();
    void dataAdded(DataManager::DataType type, const QString &key, const QVariantMap &value);
    void dataAboutToBeRemoved(DataManager::DataType type, const QString &key, const QVariantMap &value);
    void dataChanged(DataManager::DataType type, const QString &key, const QVariantMap &value);

    void sortKeyChanged(const QString &sortKey);
    void cacheKeyChanged(const QString &cacheKey);

private:
    AbstractTwitterModel *q;
    JSONParser parser;
    QByteArray buffer;
    QPointer<QNetworkReply> connection;
};

AbstractTwitterModel::Private::Private(AbstractTwitterModel *parent)
    : QObject(parent)
    , xrlLimit(0)
    , xrlRemaining(0)
    , enabled(true)
    , isLoading(false)
    , pushOrder(PushNewerToOlder)
    , filtering(false)
    , q(parent)
{
    ids.append("0");
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer.setSingleShot(false);
    timer.setInterval(10);
    connect(&OAuthManager::instance(), SIGNAL(authorizedChanged(bool)), this, SLOT(authorizedChanged(bool)));
    connect(&parser, SIGNAL(parsed(QVariant)), this, SLOT(parsed(QVariant)));
    metaObject()->invokeMethod(q, "reload", Qt::QueuedConnection);
    connect(DataManager::instance(), SIGNAL(dataAdded(DataManager::DataType,QString,QVariantMap)), this, SLOT(dataAdded(DataManager::DataType,QString,QVariantMap)));
    connect(DataManager::instance(), SIGNAL(dataAboutToBeRemoved(DataManager::DataType,QString,QVariantMap)), this, SLOT(dataAboutToBeRemoved(DataManager::DataType,QString,QVariantMap)));
    connect(DataManager::instance(), SIGNAL(dataChanged(DataManager::DataType,QString,QVariantMap)), this, SLOT(dataChanged(DataManager::DataType,QString,QVariantMap)));
    connect(q, SIGNAL(enabledChanged(bool)), this, SLOT(enabledChanged(bool)));
}

void AbstractTwitterModel::Private::enabledChanged(bool enabled)
{
    if (enabled) {
        q->reload();
    } else {
        q->abort();
    }
}

void AbstractTwitterModel::Private::authorizedChanged(bool isAuthorized)
{
    if (isAuthorized) {
        metaObject()->invokeMethod(q, "reload", Qt::QueuedConnection);
    } else {
        reset();
    }
}
void AbstractTwitterModel::Private::reload()
{
    if (!enabled) return;
    if (isLoading) return;
    AuthorizeBy authenticationMethod = q->authenticationMethod();
    if (!OAuthManager::instance().isAuthorized()) return;

    QStringList body;

    QMap<QString, QByteArray> params;
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
            if (!value.toString().isEmpty()) {
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
            if (value.toInt(&ok) != 0 && ok) {
                params.insert(key, value.toString().toUtf8());
                body.append(QString("%1=%2").arg(key).arg(value.toString()));
            }
            break;
        case QVariant::LongLong:
            if (value.toLongLong(&ok) != 0 && ok) {
                body.append(QString("%1=%2").arg(key).arg(value.toString()));
            }
            break;
        default:
            DEBUG() << key << "not found" << value;
            DEBUG() << (int)value.type() << value.type();
            break;
        }
    }

    QByteArray acceptEncoding;
    if (q->isStreaming())
        acceptEncoding = "qcompress";
    QNetworkReply *reply = 0;
    switch (authenticationMethod) {
    case AuthorizeByHeader:
        OAuthManager::instance().setAuthorizeBy(OAuthManager::AuthorizeByHeader);
        reply = OAuthManager::instance().request(q->httpMethod(), q->api(), params, acceptEncoding);
        break;
    case AuthorizeByBody:
        OAuthManager::instance().setAuthorizeBy(OAuthManager::AuthorizeByBody);
        reply = OAuthManager::instance().request(q->httpMethod(), q->api(), params, acceptEncoding);
        break;
    case AuthorizeByUrl:
        OAuthManager::instance().setAuthorizeBy(OAuthManager::AuthorizeByUrl);
        reply = OAuthManager::instance().request(q->httpMethod(), q->api(), params, acceptEncoding);
        break;
    }

    if (reply) {
        connection = QPointer<QNetworkReply>(reply);
        buffer.clear();
        connect(reply, SIGNAL(readyRead()), this, SLOT(readData()));
        connect(reply, SIGNAL(finished()), this, SLOT(finished()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));

        isLoading = true;
        emit q->loadingChanged(isLoading);
    }
//    DEBUG() << reply->url();
}

void AbstractTwitterModel::Private::abort()
{
    if (!connection.isNull()) {
        connection->abort();
        connection->deleteLater();
    }
}

void AbstractTwitterModel::Private::reset()
{
    abort();
    parser.cancel();
    if (timer.isActive()) timer.stop();
    q->setPushOrder(PushNewerToOlder);
    q->setSortKey(QString());
    q->setCacheKey(QString());
    q->setEnabled(true);
    stack.clear();
    q->beginRemoveRows(QModelIndex(), 0, ids.count());
    ids.clear();
    q->endRemoveRows();
}

void AbstractTwitterModel::Private::readData()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply) {
        buffer.append(reply->readAll());
    }

    if (q->isStreaming()) {
        int delimiter = buffer.indexOf("\r\n");

        if (delimiter > -1) {
            int length = buffer.left(delimiter).toInt();
            if (buffer.length() < delimiter + 2 + length) return;
            QByteArray data = buffer.mid(delimiter + 2, length);
            buffer = buffer.mid(delimiter + 2 + length);
            parser.parse(data);
            if (buffer.indexOf("\r\n") > -1)
                QTimer::singleShot(100, this, SLOT(readData()));
        }
    }
}

void AbstractTwitterModel::Private::finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;
    if (q->isStreaming()) {
        q->setLoading(false);
    } else {
        if(reply->hasRawHeader("X-Rate-Limit-Limit")) {
            q->setXrlLimit(reply->rawHeader("X-Rate-Limit-Limit").toInt());
        }

        if(reply->hasRawHeader("X-Rate-Limit-Remaining")) {
            q->setXrlRemaining(reply->rawHeader("X-Rate-Limit-Remaining").toInt());
        }

        if(reply->hasRawHeader("X-Rate-Limit-Reset")) {
            uint epochSec = reply->rawHeader("X-Rate-Limit-Reset").toUInt();
            QDateTime dtEpochSec = QDateTime::fromTime_t(epochSec).toLocalTime();
            q->setXrlReset(dtEpochSec);
        }

        if (reply->error() == QNetworkReply::NoError) {
            parser.parse(buffer);
        } else {
            int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            if (httpStatusCode == 429)
            {
                if (xrlRemaining == 0) {
                    emit q->rateLimitExceeded(xrlLimit, xrlRemaining, xrlReset);
                }
            }

            q->setLoading(false);
        }
    }
//    DEBUG();
    reply->deleteLater();
}

void AbstractTwitterModel::Private::error(QNetworkReply::NetworkError error)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    DEBUG() << error << reply->errorString() << reply->url() << reply->readAll();
}

void AbstractTwitterModel::Private::parsed(const QVariant &result)
{
//    DEBUG() << result.toList().length();
    q->parseDone(result);
//    DEBUG() << queue.size() << timer.isActive();
    if (!stack.isEmpty() && !timer.isActive()) {
        timer.start();
    }
    if (stack.isEmpty() && !q->isStreaming()) {
        q->setLoading(false);
    }
}

void AbstractTwitterModel::Private::timeout()
{
//    DEBUG() << q->metaObject()->className() << stack.size() << ids.size();
    if (stack.isEmpty()) {
        if (!q->isStreaming()) {
            q->setLoading(false);
        }
        timer.stop();
        return;
    }
    int size = ids.size();

    int previousSize = ids.size();

    DataManager *dataManager = DataManager::instance();

    if (pushOrder == PushAtOnce) {
        // check filtering first
        int size = stack.size() - 1;
        for (int i = size; i > -1; i--) {
            filtering = false;
            QVariantMap item = stack.at(i).second.toMap();
//            DEBUG() << q->metaObject()->className() << item.value("user").toMap().value("screen_name").toString();
            emit q->filtering(item);
//            DEBUG() << item.value("user").toMap().value("screen_name").toString() << filtering;
            if (filtering) {
                stack.takeAt(i);
                size--;
            }
        }
        q->beginInsertRows(QModelIndex(), 0, size);
    }

    bool end = false;
    while (!stack.isEmpty() && !end) {
        QPair<Action, QVariant> action;
        switch (pushOrder) {
        case PushOlderToNewer:
            action = stack.takeLast();
            break;
        default:
            action = stack.takeFirst();
            break;
        }
        switch (action.first) {
        case Private::Add: {
            QVariantMap item = action.second.toMap();
            if (sortKey.isNull()) {
                QString id = item.value("id_str").toString();
                if (pushOrder != PushAtOnce) {
                    filtering = false;
                    emit q->filtering(item);
                    if (filtering) {
                        continue;
                    }
                }
                if (!ids.contains(id)) {
                    if (pushOrder != PushAtOnce)
                        q->beginInsertRows(QModelIndex(), size - 1, size - 1);
                    dataManager->addData(q->dataType(), id, item, q->dataIsReliable());
                    ids.insert(size - 1, id);
                    size++;
                    if (pushOrder != PushAtOnce) {
                        q->endInsertRows();
                        end = true;
                    }
                }
            } else {
                if (!item.contains(sortKey)) {
                    DEBUG() << q->metaObject()->className() << item;
                }
                QString id_str = item.value(sortKey).toString();
                if (!id_str.isEmpty() && !ids.contains(id_str)) {
                    bool done = false;
                    if (pushOrder != PushAtOnce) {
                        filtering = false;
                        emit q->filtering(item);
                        if (filtering) {
                            continue;
                        }
                    }
                    for (int i = 0; i < size; i++) {
//                        DEBUG() << ids.at(i) << ids.at(i).length();
//                        DEBUG() << id << id.length();
//                        DEBUG() << (ids.at(i).length() < id.length()) << (ids.at(i) < id) << (ids.at(i).length() < id.length() || ids.at(i) < id);
                        if (ids.at(i).length() < id_str.length() || (ids.at(i).length() == id_str.length() && ids.at(i) < id_str)) {
                            if (pushOrder != PushAtOnce)
                                q->beginInsertRows(QModelIndex(), i, i);
                            dataManager->addData(q->dataType(), id_str, item, q->dataIsReliable());
                            ids.insert(i, id_str);
                            size++;
                            if (pushOrder != PushAtOnce) {
                                q->endInsertRows();
                                end = true;
                            }
                            done = true;
                            break;
                        }
                    }
                    if (!done) DEBUG() << id_str;
                }
            }
        }
            break;
        case Private::Update: {
            QVariantMap item = action.second.toMap();
            QString id = item.value("id_str").toString();
            for (int i = 0; i < size - 1; i++) {
                if (ids.at(i) == id) {
                    emit q->dataChanged(q->index(i), q->index(i));
                    break;
                }
            }
        }
            break;
        case Private::Remove: {
        }
            break;
        }

    }

    if (pushOrder == PushAtOnce)
        q->endInsertRows();

    if (previousSize != ids.size()) {
        emit q->idListChanged(ids);
        emit q->sizeChanged(ids.size() - 1);
    }

    if (stack.isEmpty()) {
        if (!q->isStreaming()) {
            q->setLoading(false);
        }
        timer.stop();
    }
}

void AbstractTwitterModel::Private::dataAdded(DataManager::DataType type, const QString &key, const QVariantMap &value)
{
    if (q->dataType() == type) {
        q->dataAdded(key, value);
    }
}

void AbstractTwitterModel::Private::dataAboutToBeRemoved(DataManager::DataType type, const QString &key, const QVariantMap &value)
{
    Q_UNUSED(value)
    if (q->dataType() == type) {
        q->dataAboutToBeRemoved(key);
    }
}

void AbstractTwitterModel::Private::dataChanged(DataManager::DataType type, const QString &key, const QVariantMap &value)
{
    if (type == q->dataType()) {
        if (ids.contains(key)) {
//            DEBUG() << DataManager::instance()->getData(type, key);
//            DEBUG() << value;
            stack.append(QPair<Private::Action, QVariant>(Update, value));
        }
        q->dataChanged(key, value);
    }
}

void AbstractTwitterModel::Private::sortKeyChanged(const QString &sortKey)
{
    // TODO: restore data
}

void AbstractTwitterModel::Private::cacheKeyChanged(const QString &cacheKey)
{
    // TODO: restore data
}

AbstractTwitterModel::AbstractTwitterModel(QObject *parent)
    : QAbstractListModel(parent)
    , d(new Private(this))
{
}

void AbstractTwitterModel::setLoading(bool loading)
{
    if (d->isLoading == loading) return;
    d->isLoading = loading;
    emit loadingChanged(loading);
}

AbstractTwitterModel::PushOrder AbstractTwitterModel::pushOrder() const
{
    return d->pushOrder;
}

void AbstractTwitterModel::setPushOrder(PushOrder pushOrder)
{
    if (d->pushOrder == pushOrder) return;
    d->pushOrder = pushOrder;
    emit pushOrderChanged(pushOrder);
}

void AbstractTwitterModel::setParameters(const QVariantMap &parameters)
{
    const QMetaObject *mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty prop = mo->property(i);
        const char *key = prop.name();
        if (QString(key) == QLatin1String("loading")) continue;
        if (QString(key) == QLatin1String("size")) continue;
        if (parameters.contains(key)) {
            setProperty(key, parameters.value(key));
        }
    }
}

bool AbstractTwitterModel::isEnabled() const
{
    return d->enabled;
}

void AbstractTwitterModel::setEnabled(bool enabled)
{
    if (d->enabled == enabled) return;
    d->enabled = enabled;
    emit enabledChanged(enabled);
}

bool AbstractTwitterModel::isLoading() const
{
    return d->isLoading;
}

const QStringList &AbstractTwitterModel::idList() const
{
    return d->ids;
}

int AbstractTwitterModel::size() const
{
    return d->ids.size() - 1;
}

const QString &AbstractTwitterModel::sortKey() const
{
    return d->sortKey;
}

void AbstractTwitterModel::setSortKey(const QString &sortKey)
{
    if (d->sortKey == sortKey) return;
    d->sortKey = sortKey;
    emit sortKeyChanged(sortKey);
}

const QString &AbstractTwitterModel::cacheKey() const
{
    return d->cacheKey;
}

void AbstractTwitterModel::setCacheKey(const QString &cacheKey)
{
    if (d->cacheKey == cacheKey) return;
    d->cacheKey = cacheKey;
    emit cacheKeyChanged(cacheKey);
}

int AbstractTwitterModel::xrlLimit() const
{
    return d->xrlLimit;
}

void AbstractTwitterModel::setXrlLimit(const int &xrlLimit)
{
    if (d->xrlLimit == xrlLimit) return;
    d->xrlLimit = xrlLimit;
    emit xrlLimitChanged(xrlLimit);
}

int AbstractTwitterModel::xrlRemaining() const
{
    return d->xrlRemaining;
}

void AbstractTwitterModel::setXrlRemaining(const int &xrlRemaining)
{
    if (d->xrlRemaining == xrlRemaining) return;
    d->xrlRemaining = xrlRemaining;
    emit xrlRemainingChanged(xrlRemaining);
}

const QDateTime &AbstractTwitterModel::xrlReset() const
{
    return d->xrlReset;
}

void AbstractTwitterModel::setXrlReset(const QDateTime &xrlReset)
{
    if (d->xrlReset == xrlReset) return;
    d->xrlReset = xrlReset;
    emit xrlResetChanged(xrlReset);
}

void AbstractTwitterModel::reload()
{
    if (!d->enabled) return;
    d->reload();
}

void AbstractTwitterModel::abort()
{
    d->abort();
}

void AbstractTwitterModel::reset()
{
    setLoading(true);
    d->reset();
    setLoading(false);
}

int AbstractTwitterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return size();
}

QVariant AbstractTwitterModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    if (index.row() < 0 || index.row() >= size())
        return ret;

    if (roleNames().contains(role)) {
        ret = DataManager::instance()->getData(dataType(), d->ids.at(index.row())).value(roleNames().value(role));
    } else {
        DEBUG() << role << "not found in" << roleNames();
    }
//    DEBUG() << roleNames().value(role) << ret;
    return ret;
}

QVariantMap AbstractTwitterModel::get(int index) const
{
    QVariantMap ret;
    if (index < 0 || index >= size()) return ret;
    ret = DataManager::instance()->getData(dataType(), d->ids.at(index));
    return ret;
}

int AbstractTwitterModel::indexOf(const QString &id) const
{
    return d->ids.indexOf(id);
}

bool AbstractTwitterModel::isStreaming() const
{
    return false;
}

void AbstractTwitterModel::addData(const QVariantMap &value)
{
    d->stack.append(QPair<Private::Action, QVariant>(Private::Add, value));
    if (!d->timer.isActive()) {
        d->timer.start();
    }
}

void AbstractTwitterModel::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    Q_UNUSED(value)
}

void AbstractTwitterModel::removeData(const QString &key)
{
    int i = d->ids.indexOf(key);
    if (i > -1) {
        beginRemoveRows(QModelIndex(), i, i);
        d->ids.removeAt(i);
        endRemoveRows();
        emit idListChanged(d->ids);
        emit sizeChanged(d->ids.size() - 1);
    }
}

void AbstractTwitterModel::dataAboutToBeRemoved(const QString &key)
{
    removeData(key);
}

void AbstractTwitterModel::dataChanged(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    Q_UNUSED(value)
}

void AbstractTwitterModel::filter() {
    d->filtering = true;
}

#if QT_VERSION >= 0x050000
QQmlListProperty<QObject> AbstractTwitterModel::childObjects()
{
    return QQmlListProperty<QObject>(this, d->childObjects);
}

void AbstractTwitterModel::setRoleNames(const QHash<int, QByteArray> &roleNames)
{
    d->roleNames = roleNames;
}

QHash<int, QByteArray> AbstractTwitterModel::roleNames() const
{
    return d->roleNames;
}
#else
QDeclarativeListProperty<QObject> AbstractTwitterModel::childObjects()
{
    return QDeclarativeListProperty<QObject>(this, d->childObjects);
}
#endif

#include "abstracttwittermodel.moc"
