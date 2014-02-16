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

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include "twitter4qml_global.h"

class TWITTER4QML_EXPORT DataManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(DataType)
public:
    enum DataType {
        NoData,
        StatusData,
        DirectMessageData,
        UserData,
        ListData,
        SearchData,
        SavedSearchData
    };

    static DataManager *instance();

    bool contains(DataManager::DataType type, const QString &key) const;
    QVariantMap getData(DataManager::DataType type, const QString &key) const;

public slots:
    void addData(DataManager::DataType type, const QString &key, const QVariantMap &value, bool reliable = true);
    void removeData(DataManager::DataType type, const QString &key);
    void setData(DataManager::DataType type, const QString &key, const QVariantMap &value);

signals:
    void dataAdded(DataManager::DataType type, const QString &key, const QVariantMap &value);
    void dataAboutToBeRemoved(DataManager::DataType type, const QString &key, const QVariantMap &value);
    void dataChanged(DataManager::DataType type, const QString &key, const QVariantMap &value);

private:
    explicit DataManager(QObject *parent = 0);
    Q_DISABLE_COPY(DataManager)
    class Private;
    Private *d;
};

#endif // DATAMANAGER_H
