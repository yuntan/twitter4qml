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
        emit q->dataAboutToBeRemoved(type, key);
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
