/* Copyright (c) 2012 Twitter4QML Project.
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

#ifndef ABSTRACTTWITTERMODEL_H
#define ABSTRACTTWITTERMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QStringList>
#include <QtCore/QUrl>
#include <QtDeclarative/QDeclarativeListProperty>

#include "twitter4qml_global.h"
#include "datamanager.h"

class AbstractTwitterModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged DESIGNABLE false)
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(PushOrder pushOrder READ pushOrder WRITE setPushOrder NOTIFY pushOrderChanged DESIGNABLE false)
    Q_PROPERTY(QStringList idList READ idList NOTIFY idListChanged DESIGNABLE false)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged DESIGNABLE false)
    Q_PROPERTY(bool streaming READ isStreaming NOTIFY streamingChanged DESIGNABLE false)
    Q_PROPERTY(QString sortKey READ sortKey WRITE setSortKey NOTIFY sortKeyChanged DESIGNABLE false)
    Q_PROPERTY(QString cacheKey READ cacheKey WRITE setCacheKey NOTIFY cacheKeyChanged DESIGNABLE false)
    Q_PROPERTY(QDeclarativeListProperty<QObject> childObjects READ childObjects DESIGNABLE false)
    Q_ENUMS(PushOrder)
    Q_CLASSINFO("DefaultProperty", "childObjects")
    Q_DISABLE_COPY(AbstractTwitterModel)
public:
    enum AuthorizeBy {
        AuthorizeByNothing,
        AuthorizeByHeader,
        AuthorizeByBody,
        AuthorizeByUrl
    };
    enum PushOrder {
        PushNewerToOlder,
        PushOlderToNewer,
        PushAtOnce
    };

    explicit AbstractTwitterModel(QObject *parent = 0);
    
    bool isEnabled() const;
    virtual bool isLoading() const;
    PushOrder pushOrder() const;
    const QStringList &idList() const;
    int size() const;
    const QString &sortKey() const;
    void setSortKey(const QString &sortKey);
    const QString &cacheKey() const;
    void setCacheKey(const QString &cacheKey);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariantMap get(int index) const;
    Q_INVOKABLE int indexOf(const QString &id) const;
    QDeclarativeListProperty<QObject> childObjects();

    virtual DataManager::DataType dataType() const { return DataManager::NoData; }
    virtual bool dataIsReliable() const { return true; }

public slots:
    void setEnabled(bool enabled);
    virtual void reload();
    void setPushOrder(PushOrder pushOrder);
    void abort();
    void filter();

signals:
    void enabledChanged(bool enabled);
    void loadingChanged(bool loading);
    void pushOrderChanged(PushOrder pushOrder);
    void idListChanged(const QStringList &idList);
    void sizeChanged(int size);
    void streamingChanged();
    void sortKeyChanged(const QString &sortKey);
    void cacheKeyChanged(const QString &cacheKey);

    void filtering(const QVariantMap &value);

protected slots:
    virtual void setLoading(bool loading);

protected:
    void setParameters(const QVariantMap &parameters);

    virtual bool isStreaming() const;
    virtual QUrl api() const = 0;
    virtual AuthorizeBy authenticationMethod() const = 0;
    virtual QString httpMethod() const = 0;
    virtual void parseDone(const QVariant &result) = 0;

    virtual void addData(const QVariantMap &value);
    virtual void dataAdded(const QString &key, const QVariantMap &value);
    virtual void removeData(const QString &key);
    virtual void dataAboutToBeRemoved(const QString &key);
    virtual void dataChanged(const QString &key, const QVariantMap &value);
    using QAbstractListModel::dataChanged;

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTTWITTERMODEL_H
