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

#include "datamanager.h"

#include "twitter4qml_global.h"

#include <QtCore/QCache>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtGui/QDesktopServices>

class DataManager::Private : public QObject
{
    Q_OBJECT
public:
    Private(DataManager *parent);
    bool contains(DataType type, const QString &key) const;
    QVariantMap get(DataType type, const QString &key) const;
    void add(DataType type, const QString &key, const QVariantMap &value, bool reliable = true);
    void remove(DataType type, const QString &key);
    void set(DataType type, const QString &key, const QVariantMap &value);

private:
    DataManager *q;
    QMap< DataType, QMap<QString, QVariantMap> > data;
};

DataManager::Private::Private(DataManager *parent)
    : QObject(parent)
    , q(parent)
{
    qRegisterMetaType<DataManager::DataType>("DataManager::DataType");
}

bool DataManager::Private::contains(DataType type, const QString &key) const
{
    return data.value(type).contains(key);
}

QVariantMap DataManager::Private::get(DataType type, const QString &key) const
{
    return data.value(type).value(key);
}

void DataManager::Private::add(DataType type, const QString &key, const QVariantMap &value, bool reliable)
{
    if (data.value(type).contains(key)) {
        if (reliable)
            set(type, key, value);
    } else {
        data[type].insert(key, value);
        if (reliable)
            emit q->dataAdded(type, key, value);
    }
}

void DataManager::Private::remove(DataType type, const QString &key)
{
    if (data.value(type).contains(key)) {
        emit q->dataAboutToBeRemoved(type, key, data.value(type).value(key));
        data[type].remove(key);
    }
}

void DataManager::Private::set(DataType type, const QString &key, const QVariantMap &value)
{
    if (data.value(type).contains(key)) {
        if (data.value(type).value(key) != value) {
            DEBUG() << data.value(type).value(key);
            DEBUG() << value;
            data[type][key] = value;
            emit q->dataChanged(type, key, value);
        }
    } else {
        add(type, key, value);
    }
}

DataManager *DataManager::instance()
{
    static DataManager ret;
    return &ret;
}

DataManager::DataManager(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

bool DataManager::contains(DataType type, const QString &key) const
{
    return d->contains(type, key);
}

QVariantMap DataManager::getData(DataType type, const QString &key) const
{
    return d->get(type, key);
}

void DataManager::addData(DataType type, const QString &key, const QVariantMap &value, bool reliable)
{
    d->add(type, key, value, reliable);
}

void DataManager::removeData(DataType type, const QString &key)
{
    d->remove(type, key);
}

void DataManager::setData(DataType type, const QString &key, const QVariantMap &value)
{
    d->set(type, key, value);
}

#include "datamanager.moc"
