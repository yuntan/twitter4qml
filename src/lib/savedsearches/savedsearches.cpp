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

#include "savedsearches.h"
#include "createsavedsearch.h"
#include "destroysavedsearch.h"

class SavedSearches::Private : public QObject
{
    Q_OBJECT
public:
    Private(SavedSearches *parent);

    bool loading;
    void create(const QVariantMap &parameters);
    void destroy(const QVariantMap &parameters);

private slots:
    void setLoading(bool loading);
    void dataChanged(const QVariant &data);

private:
    SavedSearches *q;
    QList<AbstractTwitterAction *> tasks;
};

SavedSearches::Private::Private(SavedSearches *parent)
    : QObject(parent)
    , loading(false)
    , q(parent)
{
}

void SavedSearches::Private::create(const QVariantMap &parameters)
{
    CreateSavedSearch *action = new CreateSavedSearch(this);
    action->query(parameters.value("query").toString());
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void SavedSearches::Private::destroy(const QVariantMap &parameters)
{
    DestroySavedSearch *action = new DestroySavedSearch(this);
    action->id(parameters.value("id").toString());
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void SavedSearches::Private::dataChanged(const QVariant &data)
{
    QVariantMap map = data.toMap();
//    DEBUG() << data;
    if (qobject_cast<CreateSavedSearch *>(sender())) {
        if (map.contains("id_str")) {
            DataManager::instance()->addData(q->dataType(), map.value("id_str").toString(), map);
        }
        sender()->deleteLater();
    }
    if (qobject_cast<DestroySavedSearch *>(sender())) {
        if (map.contains("id_str")) {
            DataManager::instance()->removeData(q->dataType(), map.value("id_str").toString());
        }
        sender()->deleteLater();
    }
    if (tasks.isEmpty()) {
        setLoading(false);
    } else {
        tasks.takeFirst()->exec();
    }
}

void SavedSearches::Private::setLoading(bool l)
{
    if (loading == l) return;
    loading = l;
    emit q->loadingChanged(l);
}

SavedSearches::SavedSearches(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private(this))
{
    QHash<int, QByteArray> roles;
    roles[created_at_role] = "created_at";
    roles[id_role] = "id";
    roles[id_str_role] = "id_str";
    roles[name_role] = "name";
    roles[position_role] = "position";
    roles[query_role] = "query";
    setRoleNames(roles);
}

void SavedSearches::createSavedSearch(QVariantMap parameters)
{
    d->create(parameters);
}

void SavedSearches::destroySavedSearch(QVariantMap parameters)
{
    d->destroy(parameters);
}

void SavedSearches::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    addData(value);
}

void SavedSearches::dataAboutToBeRemoved(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(value)
    removeData(key);
}

bool SavedSearches::isLoading() const
{
    return AbstractTwitterModel::isLoading() || d->loading;
}

void SavedSearches::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                QVariantMap map = result.toMap();
                map.insert("id_str", map.value("id").toString());
                addData(map);
            }
        }
    }
}

#include "savedsearches.moc"
