#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

class DataManager : public QObject
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
