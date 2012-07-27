#include "unionmodel.h"

#include "twitter4qml_global.h"
#include "../tools/abstracttwittermodel.h"
#include "../tools/datamanager.h"

#include <QtCore/QStringList>

class UnionModel::Private : public QObject
{
    Q_OBJECT
public:
    Private(UnionModel *parent);

    bool isLoading;
    QList<QObject *> childObjects;
    QList<AbstractTwitterModel *> models;
    QStringList ids;
    DataManager::DataType dataType;
    static void appendFunction(QDeclarativeListProperty<QObject> *list, QObject *object);
    static int countFunction(QDeclarativeListProperty<QObject> *list);
    static QObject *atFunction(QDeclarativeListProperty<QObject> *list, int index);
    void append(QObject *object);

private slots:
    void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);
    void rowsInserted(const QModelIndex &parent, int start, int end);
    void rowsAboutToBeRemoved(const QModelIndex & parent, int start, int end);
    void loadingChanged();

private:
    UnionModel *q;
};

void UnionModel::Private::appendFunction(QDeclarativeListProperty<QObject> *list, QObject *object)
{
    UnionModel::Private *d = qobject_cast<UnionModel::Private *>(list->object);
    if (d) {
        d->append(object);
    }
}

int UnionModel::Private::countFunction(QDeclarativeListProperty<QObject> *list)
{
    int ret = -1;
    UnionModel::Private *d = qobject_cast<UnionModel::Private *>(list->object);
    if (d) {
        ret = d->childObjects.count();
    }
    return ret;
}

QObject *UnionModel::Private::atFunction(QDeclarativeListProperty<QObject> *list, int index)
{
    QObject *ret = 0;
    UnionModel::Private *d = qobject_cast<UnionModel::Private *>(list->object);
    if (d) {
        ret = d->childObjects.at(index);
    }
    return ret;
}

void UnionModel::Private::append(QObject *object)
{
    childObjects.append(object);
    AbstractTwitterModel *model = qobject_cast<AbstractTwitterModel *>(object);
    if (model) {
        if (models.isEmpty()) {
            models.append(model);
            dataType = model->dataType();
            q->setRoleNames(model->roleNames());
            connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChanged(QModelIndex,QModelIndex)));
            connect(model, SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(rowsInserted(QModelIndex,int,int)));
            connect(model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this, SLOT(rowsAboutToBeRemoved(QModelIndex, int, int)));
            connect(model, SIGNAL(loadingChanged(bool)), this, SLOT(loadingChanged()));
        } else {
            if (dataType == model->dataType()) {
                if (q->roleNames() == model->roleNames()) {
                    models.append(model);
                    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChanged(QModelIndex,QModelIndex)));
                    connect(model, SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(rowsInserted(QModelIndex,int,int)));
                    connect(model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this, SLOT(rowsAboutToBeRemoved(QModelIndex, int, int)));
                    connect(model, SIGNAL(loadingChanged(bool)), this, SLOT(loadingChanged()));
                } else {
                    DEBUG() << q->roleNames() << model->roleNames();
                }
            }
        }
        loadingChanged();
    } else {
        DEBUG() << object;
    }
}

UnionModel::Private::Private(UnionModel *parent)
    : QObject(parent)
    , isLoading(false)
    , dataType(DataManager::NoData)
    , q(parent)
{
    ids.append("0");
}

void UnionModel::Private::dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
//    AbstractTwitterModel *model = qobject_cast<AbstractTwitterModel *>(sender());
//    DEBUG() << topLeft << bottomRight << sender();
}

void UnionModel::Private::rowsInserted(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent)
//    DEBUG() << parent << start << end << sender();
    AbstractTwitterModel *model = qobject_cast<AbstractTwitterModel *>(sender());

    bool allAdd = ids.count() == 1;

    if (allAdd)
        q->beginInsertRows(QModelIndex(), 0, end - start);
    for (int i = start; i < end + 1; i++) {
        QString id_str = model->get(i).value("id_str").toString();
        if (!ids.contains(id_str)) {
            for (int j = 0; j < ids.size(); j++) {
                if (ids.at(j).length() < id_str.length() || (ids.at(j).length() == id_str.length() && ids.at(j) < id_str)) {
                    if (!allAdd)
                        q->beginInsertRows(QModelIndex(), j, j);
                    ids.insert(j, id_str);
                    if (!allAdd)
                        q->endInsertRows();
                    break;
                }
            }
        }
    }
    if (allAdd)
        q->endInsertRows();
    emit q->idListChanged(ids);
    emit q->sizeChanged();
}

void UnionModel::Private::rowsAboutToBeRemoved(const QModelIndex & parent, int start, int end)
{
    Q_UNUSED(parent)
    AbstractTwitterModel *model = qobject_cast<AbstractTwitterModel *>(sender());
    for (int i = start; i < end + 1; i++) {
        QString id = model->get(i).value("id_str").toString();
        int j = ids.indexOf(id);
        if (j > -1) {
            q->beginRemoveRows(QModelIndex(), j, j);
            ids.removeAt(j);
            q->endRemoveRows();
        }
    }
    emit q->idListChanged(ids);
    emit q->sizeChanged();
}

void UnionModel::Private::loadingChanged() {
    bool loading = false;
    foreach (const AbstractTwitterModel *model, models) {
//        DEBUG() << model << model->isLoading();
        if (model->isLoading()) {
            loading = true;
            break;
        }
    }
//    DEBUG() << loading;
    if (isLoading == loading) return;
    isLoading = loading;
    emit q->loadingChanged(loading);
}

UnionModel::UnionModel(QObject *parent)
    : QAbstractListModel(parent)
    , d(new Private(this))
{
}

int UnionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->ids.size() - 1;
}

QVariant UnionModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    if (index.row() < 0 || index.row() >= d->ids.length() - 1)
        return ret;

    if (roleNames().contains(role)) {
        ret = DataManager::instance()->getData(d->dataType, d->ids.at(index.row())).value(roleNames().value(role));
    } else {
        DEBUG() << role << "not found in" << roleNames();
    }
//    DEBUG() << roleNames().value(role) << ret;
    return ret;
}

bool UnionModel::isLoading() const
{
    return d->isLoading;
}

void UnionModel::addModel(QObject *model) const
{
    d->append(model);
}

QVariantMap UnionModel::get(int index) const
{
    QVariantMap ret;
    if (index < 0 || index >= d->ids.length() - 1) return ret;
    ret = DataManager::instance()->getData(d->dataType, d->ids.at(index));
    return ret;
}

void UnionModel::reload()
{
    foreach (AbstractTwitterModel *model, d->models) {
        model->reload();
    }
}

const QStringList &UnionModel::idList() const
{
    return d->ids;
}

int UnionModel::indexOf(const QString &id)
{
    return d->ids.indexOf(id);
}

QDeclarativeListProperty<QObject> UnionModel::childObjects()
{
    return QDeclarativeListProperty<QObject>(d, 0, &Private::appendFunction, &Private::countFunction, &Private::atFunction);
}

#include "unionmodel.moc"
