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

#ifndef UNIONMODEL_H
#define UNIONMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QStringList>
#if QT_VERSION >= 0x050000
#include <QtQml/QQmlListProperty>
#else
#include <QtDeclarative/QDeclarativeListProperty>
#endif

class UnionModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged DESIGNABLE false)
#if QT_VERSION >= 0x050000
    Q_PROPERTY(QQmlListProperty<QObject> childObjects READ childObjects DESIGNABLE false)
#else
    Q_PROPERTY(QDeclarativeListProperty<QObject> childObjects READ childObjects DESIGNABLE false)
#endif
    Q_PROPERTY(QStringList idList READ idList NOTIFY idListChanged DESIGNABLE false)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged DESIGNABLE false)
    Q_CLASSINFO("DefaultProperty", "childObjects")
    Q_DISABLE_COPY(UnionModel)
public:
    explicit UnionModel(QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    
    virtual bool isLoading() const;
#if QT_VERSION >= 0x050000
    QQmlListProperty<QObject> childObjects();
#else
    QDeclarativeListProperty<QObject> childObjects();
#endif

    Q_INVOKABLE void addModel(QObject *model) const;
    Q_INVOKABLE void clearModel() const;
    Q_INVOKABLE QVariantMap get(int index) const;
    const QStringList &idList() const;
    Q_INVOKABLE int size() { return rowCount(); }
    Q_INVOKABLE int indexOf(const QString &id);

#if QT_VERSION >= 0x050000
    QHash<int, QByteArray> roleNames() const;
#endif

public slots:
    void reload();

signals:
    void loadingChanged(bool loading);
    void idListChanged(const QStringList &idList);
    void sizeChanged();

protected:
#if QT_VERSION >= 0x050000
    void setRoleNames(const QHash<int, QByteArray> &roleNames);
#endif

private:
    class Private;
    Private *d;
};

#endif // UNIONMODEL_H
