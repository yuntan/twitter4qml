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
    DEBUG() << parameters;
    CreateSavedSearch *action = new CreateSavedSearch(this);
    action->setQuery(parameters.value("query").toString());
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
    DEBUG() << parameters;
    DestroySavedSearch *action = new DestroySavedSearch(this);
    action->setId(parameters.value("id").toString());
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
    roles[CreatedAtRole] = "created_at";
    roles[IdRole] = "id";
    roles[IdStrRole] = "id_str";
    roles[NameRole] = "name";
    roles[PositionRole] = "position";
    roles[QueryRole] = "query";
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
