#include "datamanager.h"

#include "twitter4qml_global.h"

#include <QtCore/QCache>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtGui/QDesktopServices>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

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

private slots:
    void dataAdded(DataManager::DataType type, const QString &key, const QVariantMap &value);
    void dataAboutToBeRemoved(DataManager::DataType type, const QString &key);
    void dataChanged(DataManager::DataType type, const QString &key, const QVariantMap &value);

private:
    void setupDatabase();
    bool insertData(DataType type, const QString &key, const QVariantMap &value);
    bool deleteData(DataType type, const QString &key);
    bool updateData(DataType type, const QString &key, const QVariantMap &value);

private:
    DataManager *q;
    QMap< DataType, QCache<QString, QVariantMap> > cacheMap;
    QMap< DataType, QMap<QString, QVariantMap> > data;
    QSqlDatabase db;
};

DataManager::Private::Private(DataManager *parent)
    : QObject(parent)
    , q(parent)
{
//    setupDatabase();
    qRegisterMetaType<DataManager::DataType>("DataManager::DataType");
    connect(q, SIGNAL(dataAdded(DataManager::DataType,QString,QVariantMap)), this, SLOT(dataAdded(DataManager::DataType,QString,QVariantMap)), Qt::QueuedConnection);
    connect(q, SIGNAL(dataChanged(DataManager::DataType,QString,QVariantMap)), this, SLOT(dataChanged(DataManager::DataType,QString,QVariantMap)), Qt::QueuedConnection);
    connect(q, SIGNAL(dataAboutToBeRemoved(DataManager::DataType,QString)), this, SLOT(dataAboutToBeRemoved(DataManager::DataType,QString)), Qt::QueuedConnection);
}

void DataManager::Private::setupDatabase()
{
    QString dataPath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QDir dir;
    if (!dir.mkpath(dataPath)) {
        qWarning() << "QDir::mkpath(" << dataPath << ") failed.";
    } else {
//        QFile::remove(QString("%1/database.db").arg(dataPath));
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(QString("%1/database.db").arg(dataPath));

        if (!db.open()) {
            qWarning() << db.lastError().text() << db.databaseName();
        } else {
            QSqlQuery query;
            query.prepare("PRAGMA foreign_keys = ON;");
            if (!query.exec()) {
                DEBUG() << query.lastError().text() << query.lastQuery();
            }
            int version = -1;
            if (!db.tables().isEmpty()) {
                query.prepare("SELECT version from Version;");
                if (!query.exec()) {
                    DEBUG() << query.lastError().text() << query.lastQuery();
                }
                if (query.first()) {
                    version = query.value(query.record().indexOf("version")).toInt();
                }
            }

            DEBUG() << "version" << version;
            QDir dir(":/twitter4qml/sql");
            foreach (const QString &sql, dir.entryList(QStringList() << "*", QDir::Files, QDir::Name)) {
                if (sql.toInt() > version) {
                    db.transaction();
                    QFile file(dir.absoluteFilePath(sql));
                    file.open(QFile::ReadOnly | QFile::Text);
                    QString str = QString::fromUtf8(file.readAll());
                    file.close();
//                    DEBUG() << str;
                    query.prepare(str);
                    if (!query.exec()) {
                        DEBUG() << query.lastError().text() << query.lastQuery();
                        db.rollback();
                        break;
                    }

                    version = sql.toInt();
                    if (version == 0)
                        query.prepare("INSERT INTO Version(version) VALUES(?);");
                    else
                        query.prepare("UPDATE Version SET version = ?;");
                    query.addBindValue(version);
                    if (!query.exec()) {
                        DEBUG() << query.lastError().text() << query.lastQuery();
                        db.rollback();
                        break;
                    }
                    db.commit();
                }
            }
            DEBUG() << "version" << version;
        }
    }
}

bool DataManager::Private::contains(DataType type, const QString &key) const
{
    return data[type].contains(key);
}

QVariantMap DataManager::Private::get(DataType type, const QString &key) const
{
    return data[type][key];
}

void DataManager::Private::add(DataType type, const QString &key, const QVariantMap &value, bool reliable)
{
    if (data[type].contains(key)) {
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
    if (data[type].contains(key)) {
        emit q->dataAboutToBeRemoved(type, key);
        data[type].remove(key);
    }
}

void DataManager::Private::set(DataType type, const QString &key, const QVariantMap &value)
{
    if (data[type].contains(key)) {
        if (data[type][key] != value) {
            data[type][key] = value;
            emit q->dataChanged(type, key, value);
        }
    } else {
        add(type, key, value);
    }
}

void DataManager::Private::dataAdded(DataManager::DataType type, const QString &key, const QVariantMap &value)
{
//    db.transaction();
//    bool ret = insertData(type, key, value);
//    if (ret) {
//        db.commit();
//    } else {
//        db.rollback();
//    }
}

bool DataManager::Private::insertData(DataManager::DataType type, const QString &key, const QVariantMap &value)
{
    QSqlQuery query(db);
    QVariantMap fields = value;
    switch (type) {
    case StatusData:
        query.prepare("SELECT tweet_id FROM Tweet WHERE id_str = ?;");
        query.addBindValue(key);
        if (!query.exec()) {
            DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues() << query.first();
            return false;
        }
        if (query.first()) {
//            DEBUG() << key << "found";
            return true;
        }

        fields.insert("type", "Status");

        if (!fields.value("contributors").isNull()) {

        }
        fields.remove("contributors");

        if (!fields.value("coordinates").isNull()) {
            QVariantMap coordinates = fields.value("coordinates").toMap();
            query.prepare("INSERT INTO Coordinates(type) VALUES(?);");
            query.addBindValue(coordinates.value("type").toString());
            if (!query.exec()) {
                DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues();
                return false;
            }
            if (!query.lastInsertId().isNull()) {
                qlonglong coordinates_id = query.lastInsertId().toLongLong();
                int sequence = 0;
                QVariantList c = coordinates.value("coordinates").toList();
                query.prepare("INSERT INTO Coordinate(coordinates_id, sequence, x, y) VALUES(?, ? ,?, ?);");
                query.addBindValue(coordinates_id);
                query.addBindValue(sequence);
                query.addBindValue(c.takeFirst());
                query.addBindValue(c.takeFirst());
                if (!query.exec()) {
                    DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues();
                    return false;
                }
                fields.insert("coordinates", coordinates_id);
            }
        }
        if (!fields.value("geo").isNull()) {
//            DEBUG() << fields.value("geo");
            QVariantMap coordinates = fields.value("geo").toMap();
            query.prepare("INSERT INTO Coordinates(type) VALUES(?);");
            query.addBindValue(coordinates.value("type").toString());
            if (!query.exec()) {
                DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues();
                return false;
            }
//            DEBUG() << query.lastInsertId();
            if (!query.lastInsertId().isNull()) {
                int coordinates_id = query.lastInsertId().toInt();
                int sequence = 0;
                QVariantList c = coordinates.value("coordinates").toList();
                query.prepare("INSERT INTO Coordinate(coordinates_id, sequence, x, y) VALUES(?, ? ,?, ?);");
                query.addBindValue(coordinates_id);
                query.addBindValue(sequence);
                query.addBindValue(c.takeFirst());
                query.addBindValue(c.takeFirst());
                if (!query.exec()) {
                    DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues();
                    return false;
                }
                fields.insert("geo", coordinates_id);
            }
        }

        fields.remove("id");

        if (!fields.value("in_reply_to_user_id").isNull()) {
            QString in_reply_to_user_id = fields.value("in_reply_to_user_id").toString();
            if (!contains(UserData, in_reply_to_user_id)) {
                QVariantMap user;
                user["id_str"] = in_reply_to_user_id;
                user["screen_name"] = fields.value("in_reply_to_screen_name");
                add(UserData, in_reply_to_user_id, user);
            }
        }

        fields.remove("in_reply_to_user_id");
        fields.remove("in_reply_to_user_id_str");
        fields.remove("in_reply_to_screen_name");
        fields.remove("in_reply_to_status_id_str");

        fields.remove("media");
        fields.remove("place");
//        if (!fields.value("place").isNull()) {
//        }
        if (!fields.value("retweeted_status").isNull()) {
            if (!insertData(StatusData, fields.value("retweeted_status").toMap().value("id_str").toString(), fields.value("retweeted_status").toMap())) {
                DEBUG();
                return false;
            }
            query.prepare("SELECT tweet_id FROM Tweet WHERE id_str = ?;");
            query.addBindValue(fields.value("retweeted_status").toMap().value("id_str"));
            if (!query.exec()) {
                DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues();
                return false;
            }
            if (query.first()) {
                fields.insert("retweeted_status", query.value(query.record().indexOf("tweet_id")));
            } else {
                DEBUG() << fields.value("retweeted_status") << "not found";
                return false;
            }
        }

        if (!fields.value("user").isNull()) {
            if (!insertData(UserData, fields.value("user").toMap().value("id_str").toString(), fields.value("user").toMap())) {
                DEBUG();
                return false;
            }
            query.prepare("SELECT user_id FROM User WHERE id_str = ?;");
            query.addBindValue(fields.value("user").toMap().value("id_str"));
            if (!query.exec()) {
                DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues();
                return false;
            }
            if (query.first()) {
                fields.insert("from_user", query.value(query.record().indexOf("user_id")));
            } else {
                DEBUG() << query.lastQuery() << query.boundValues();
                return false;
            }
        }
        fields.remove("user");

        {
            QStringList keys = fields.keys();
            QStringList placeholder;
            for (int i = 0; i < keys.count(); i++) {
                placeholder.append("?");
            }
            query.prepare(QString("INSERT INTO Tweet(%1) VALUES(%2);").arg(keys.join(",")).arg(placeholder.join(",")));
            foreach (const QVariant &v, fields) {
                query.addBindValue(v);
            }
            if (!query.exec()) {
                DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues();
                return false;
            }
        }
        return true;
    case UserData:
        query.prepare("SELECT user_id FROM User WHERE id_str = ?;");
        query.addBindValue(key);
        if (!query.exec()) {
            DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues() << query.first();
            return false;
        }
        if (query.first()) {
//            DEBUG() << key << "found";
            return true;
        }
        fields.remove("contributors_enabled");
        fields.remove("default_profile");
        fields.remove("default_profile_image");
        fields.remove("id");
        fields.remove("profile_background_color");
        fields.remove("profile_background_image_url");
        fields.remove("profile_background_image_url_https");
        fields.remove("profile_background_tile");
        fields.remove("profile_image_url_https");
        fields.remove("profile_link_color");
        fields.remove("profile_sidebar_border_color");
        fields.remove("profile_sidebar_fill_color");
        fields.remove("profile_text_color");
        fields.remove("profile_use_background_image");
        fields.remove("profile_text_color");
        fields.remove("profile_text_color");
        {
            QStringList keys = fields.keys();
            QStringList placeholder;
            for (int i = 0; i < keys.count(); i++) {
                placeholder.append("?");
            }
            query.prepare(QString("INSERT INTO User(%1) VALUES(%2);").arg(keys.join(",")).arg(placeholder.join(",")));
            foreach (const QVariant &v, fields) {
                query.addBindValue(v);
            }
            if (!query.exec()) {
                DEBUG() << query.lastError().text() << query.lastQuery() << query.boundValues();
                return false;
            }
        }
//        DEBUG() << "User" << fields.value("id_str").toString() << fields.value("screen_name").toString() << "is saved.";
        return true;
    default:
//        DEBUG() << type << "is not handled yet.";
        break;
    }

//    DEBUG();
    return false;
}

void DataManager::Private::dataAboutToBeRemoved(DataManager::DataType type, const QString &key)
{

}

void DataManager::Private::dataChanged(DataManager::DataType type, const QString &key, const QVariantMap &value)
{

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
