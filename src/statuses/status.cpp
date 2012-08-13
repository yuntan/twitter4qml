#include "status.h"
#include "showstatus.h"
#include "updatestatus.h"
#include "updatestatuswithmedia.h"
#include "retweetstatus.h"
#include "destroystatus.h"

#include "../tools/datamanager.h"
#include "../favorites/createfavorite.h"
#include "../favorites/destroyfavorite.h"
#include "../users/user.h"

#include "../utils.h"

#include <QtCore/QMetaProperty>

class Status::Private : public QObject
{
    Q_OBJECT
public:
    Private(Status *parent);

    bool loading;
    QVariantList contributors;
    QVariantMap coordinates;
    QString createdAt;
    QVariantMap entities;
    bool favorited;
    QVariantMap geo;
    QString idStr;
    QString inReplyToScreenName;
    QString inReplyToStatusIdStr;
    QString inReplyToUserIdStr;
    QVariantMap place;
    bool possiblySensitive;
    int retweetCount;
    bool retweeted;
    QVariantMap retweetedStatus;
    QString source;
    QString text;
    QString plainText;
    QString richText;
    bool truncated;
    QVariantMap user;
    QVariantList media;

    void update(const QVariantMap &parameters);
    void retweet(const QVariantMap &parameters);
    void destroy();
    void favorite();
    void unfavorite();

private slots:
    void setLoading(bool loading);
    void idStrChanged(const QString &idStr);
    void dataChanged(const QVariant &data);

private:
    Status *q;
    QList<AbstractTwitterAction *> tasks;
};

Status::Private::Private(Status *parent)
    : QObject(parent)
    , loading(false)
    , favorited(false)
    , possiblySensitive(false)
    , retweetCount(0)
    , retweeted(false)
    , truncated(false)
    , q(parent)
{
    connect(q, SIGNAL(idStrChanged(QString)), this, SLOT(idStrChanged(QString)));
}

void Status::Private::setLoading(bool l)
{
    if (loading == l) return;
    loading = l;
    emit q->loadingChanged(l);
}

void Status::Private::idStrChanged(const QString &id)
{
    contributors.clear();
    coordinates.clear();
    createdAt.clear();
    entities.clear();
    favorited = false;
    geo.clear();
    inReplyToScreenName.clear();
    inReplyToStatusIdStr.clear();
    inReplyToUserIdStr.clear();
    place.clear();
    possiblySensitive = false;
    retweetCount = 0;
    retweeted = false;
    retweetedStatus.clear();
    source.clear();
    text.clear();
    plainText.clear();
    richText.clear();
    truncated = false;
    user.clear();
    media.clear();
    if (id.isEmpty()) {
    } else {
        ShowStatus *action = new ShowStatus(this);
        action->setId(id);
        connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
        if (loading) {
            tasks.append(action);
        } else {
            setLoading(true);
            action->exec();
        }
    }
}

void Status::Private::update(const QVariantMap &parameters)
{
    AbstractTwitterAction *action = 0;
    if (parameters.contains("media") && !parameters.value("media").toList().isEmpty()) {
        UpdateStatusWithMedia *act = new UpdateStatusWithMedia(this);
        act->setStatus(parameters.value("status").toString());
        act->setLatitude(parameters.value("_lat").toDouble());
        act->setLongitude(parameters.value("_long").toDouble());
        act->setPlaceId(parameters.value("place_id").toString());
        act->setMedia(parameters.value("media").toList());
        act->setInReplyToStatusId(parameters.value("in_reply_to_status_id").toString());
        act->setTrimUser(false);
        act->setIncludeEntities(true);
        connect(act, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
        action = act;
    } else {
        UpdateStatus *act = new UpdateStatus(this);
        act->setStatus(parameters.value("status").toString());
        act->setLatitude(parameters.value("_lat").toDouble());
        act->setLongitude(parameters.value("_long").toDouble());
        act->setPlaceId(parameters.value("place_id").toString());
        act->setInReplyToStatusId(parameters.value("in_reply_to_status_id").toString());
        act->setTrimUser(false);
        act->setIncludeEntities(true);
        connect(act, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
        action = act;
    }
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void Status::Private::retweet(const QVariantMap &parameters)
{
    RetweetStatus *action = new RetweetStatus(this);
    action->setId(parameters.value("id").toString());
    action->setTrimUser(true);
    action->setIncludeEntities(true);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void Status::Private::destroy()
{
    DestroyStatus *action = new DestroyStatus(this);
    action->setId(idStr);
    action->setIncludeEntities(true);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void Status::Private::favorite()
{
    AbstractFavoriteAction *action = new CreateFavorite(this);
    action->setId(idStr);
    action->setIncludeEntities(true);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void Status::Private::unfavorite()
{
    AbstractFavoriteAction *action = new DestroyFavorite(this);
    action->setId(idStr);
    action->setIncludeEntities(true);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void Status::Private::dataChanged(const QVariant &data)
{
    if (qobject_cast<DestroyStatus *>(sender())) {
        DEBUG() << data;
        q->setIdStr(QString());
        emit q->dataChanged();
        qDeleteAll(tasks);
        tasks.clear();
        setLoading(false);
    }
    QObject *action = qobject_cast<QObject *>(sender());
    if (action) {
        QVariantMap status = Status::parse(data.toMap());
        const QMetaObject *mo = q->metaObject();
        for (int i = 0; i < mo->propertyCount(); i++) {
            QMetaProperty prop = mo->property(i);
            if (!prop.isDesignable()) continue;
            const char *key = prop.name();
            if (status.contains(key)) {
                if (QLatin1String("favorited") == key) {
                    if (qobject_cast<AbstractFavoriteAction *>(sender())) {
                        q->setProperty(key, !status.value(key).toBool());
                    } else {
                        q->setProperty(key, status.value(key));
                    }
                } else {
                    q->setProperty(key, status.value(key));
                }
            } else {
                q->setProperty(key, QVariant());
            }
        }
        if (!qobject_cast<RetweetStatus *>(action))
            DataManager::instance()->addData(DataManager::StatusData, q->idStr(), status);
        emit q->dataChanged();
        action->deleteLater();
    }
    if (tasks.isEmpty()) {
        setLoading(false);
    } else {
        tasks.takeFirst()->exec();
    }
}


Status::Status(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

void Status::updateStatus(QVariantMap parameters)
{
    d->update(parameters);
}

void Status::retweetStatus(QVariantMap parameters)
{
    d->retweet(parameters);
}

void Status::destroyStatus()
{
    d->destroy();
}

void Status::favorite()
{
    d->favorite();
}

void Status::unfavorite()
{
    d->unfavorite();
}

bool Status::loading() const
{
    return d->loading;
}

const QVariantList &Status::contributors() const
{
    return d->contributors;
}

void Status::setContributors(const QVariantList &contributors)
{
    if (d->contributors == contributors) return;
    d->contributors = contributors;
    emit contributorsChanged(contributors);
}

const QVariantMap &Status::coordinates() const
{
    return d->coordinates;
}

void Status::setCoordinates(const QVariantMap &coordinates)
{
    if (d->coordinates == coordinates) return;
    d->coordinates = coordinates;
    emit coordinatesChanged(coordinates);
}

const QString &Status::createdAt() const
{
    return d->createdAt;
}

void Status::setCreatedAt(const QString &createdAt)
{
    if (d->createdAt == createdAt) return;
    d->createdAt = createdAt;
    emit createdAtChanged(createdAt);
}

const QVariantMap &Status::entities() const
{
    return d->entities;
}

void Status::setEntities(const QVariantMap &entities)
{
    if (d->entities == entities) return;
    d->entities = entities;
    emit entitiesChanged(entities);
}

bool Status::favorited() const
{
    return d->favorited;
}

void Status::setFavorited(bool favorited)
{
    if (d->favorited == favorited) return;
    d->favorited = favorited;
    emit favoritedChanged(favorited);
}

const QVariantMap &Status::geo() const
{
    return d->geo;
}

void Status::setGeo(const QVariantMap &geo)
{
    if (d->geo == geo) return;
    d->geo = geo;
    emit geoChanged(geo);
}

const QString &Status::idStr() const
{
    return d->idStr;
}

void Status::setIdStr(const QString &idStr)
{
    if (d->idStr == idStr) return;
    d->idStr = idStr;
    emit idStrChanged(idStr);
}

const QString &Status::inReplyToScreenName() const
{
    return d->inReplyToScreenName;
}

void Status::setInReplyToScreenName(const QString &inReplyToScreenName)
{
    if (d->inReplyToScreenName == inReplyToScreenName) return;
    d->inReplyToScreenName = inReplyToScreenName;
    emit inReplyToScreenNameChanged(inReplyToScreenName);
}

const QString &Status::inReplyToStatusIdStr() const
{
    return d->inReplyToStatusIdStr;
}

void Status::setInReplyToStatusIdStr(const QString &inReplyToStatusIdStr)
{
    if (d->inReplyToStatusIdStr == inReplyToStatusIdStr) return;
    d->inReplyToStatusIdStr = inReplyToStatusIdStr;
    emit inReplyToStatusIdStrChanged(inReplyToStatusIdStr);
}

const QString &Status::inReplyToUserIdStr() const
{
    return d->inReplyToUserIdStr;
}

void Status::setInReplyToUserIdStr(const QString &inReplyToUserIdStr)
{
    if (d->inReplyToUserIdStr == inReplyToUserIdStr) return;
    d->inReplyToUserIdStr = inReplyToUserIdStr;
    emit inReplyToUserIdStrChanged(inReplyToUserIdStr);
}

const QVariantMap &Status::place() const
{
    return d->place;
}

void Status::setPlace(const QVariantMap &place)
{
    if (d->place == place) return;
    d->place = place;
    emit placeChanged(place);
}

bool Status::possiblySensitive() const
{
    return d->possiblySensitive;
}

void Status::setPossiblySensitive(bool possiblySensitive)
{
    if (d->possiblySensitive == possiblySensitive) return;
    d->possiblySensitive = possiblySensitive;
    emit possiblySensitiveChanged(possiblySensitive);
}

int Status::retweetCount() const
{
    return d->retweetCount;
}

void Status::setRetweetCount(int retweetCount)
{
    if (d->retweetCount == retweetCount) return;
    d->retweetCount = retweetCount;
    emit retweetCountChanged(retweetCount);
}

bool Status::retweeted() const
{
    return d->retweeted;
}

void Status::setRetweeted(bool retweeted)
{
    if (d->retweeted == retweeted) return;
    d->retweeted = retweeted;
    emit retweetedChanged(retweeted);
}

const QVariantMap &Status::retweetedStatus() const
{
    return d->retweetedStatus;
}

void Status::setRetweetedStatus(const QVariantMap &retweetedStatus)
{
    if (d->retweetedStatus == retweetedStatus) return;
    d->retweetedStatus = retweetedStatus;
    emit retweetedStatusChanged(retweetedStatus);
}

const QString &Status::source() const
{
    return d->source;
}

void Status::setSource(const QString &source)
{
    if (d->source == source) return;
    d->source = source;
    emit sourceChanged(source);
}

const QString &Status::text() const
{
    return d->text;
}

void Status::setText(const QString &text)
{
    if (d->text == text) return;
    d->text = text;
    emit textChanged(text);
}

const QString &Status::plainText() const
{
    return d->plainText;
}

void Status::setPlainText(const QString &plainText)
{
    if (d->plainText == plainText) return;
    d->plainText = plainText;
    emit plainTextChanged(plainText);
}

const QString &Status::richText() const
{
    return d->richText;
}

void Status::setRichText(const QString &richText)
{
    if (d->richText == richText) return;
    d->richText = richText;
    emit richTextChanged(richText);
}

bool Status::truncated() const
{
    return d->truncated;
}

void Status::setTruncated(bool truncated)
{
    if (d->truncated == truncated) return;
    d->truncated = truncated;
    emit truncatedChanged(truncated);
}

const QVariantMap &Status::user() const
{
    return d->user;
}

void Status::setUser(const QVariantMap &user)
{
    if (d->user == user) return;
    d->user = user;
    emit userChanged(user);
}

const QVariantList &Status::media() const
{
    return d->media;
}

void Status::setMedia(const QVariantList &media)
{
    if (d->media == media) return;
    d->media = media;
    emit mediaChanged(media);
}

QVariantMap Status::data() const
{
    QVariantMap ret;
    const QMetaObject *mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty prop = mo->property(i);
        if (!prop.isDesignable()) continue;
        const char *key = prop.name();
        ret.insert(key, property(key));
    }
    return ret;
}

bool Status::indicesGreaterThan(const QVariant &v1, const QVariant &v2)
{
    return v1.toMap().value("indices").toList().first().toInt() > v2.toMap().value("indices").toList().first().toInt();
}

void Status::debug() const
{
    const QMetaObject *mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty prop = mo->property(i);
        if (!prop.isDesignable()) continue;
        const char *key = prop.name();
        DEBUG() << key << property(key);
    }
}

QVariantMap Status::parse(const QVariantMap &status)
{
    QVariantMap ret = status;

    ret.insert("user", User::parse(ret.value("user").toMap()));

    QString text = ret.value("text").toString();
    if (ret.contains("entities") && !ret.value("entities").isNull()) {
//        DEBUG() << text;
        QString plainText = text;
        QString richText = text.replace(" ", "\t");
        QVariantList entitiesSortedByIndices;
        QVariantMap entities = ret.value("entities").toMap();
        foreach (const QString &key, entities.keys()) {
            QVariant entity = entities.value(key);
            if (entity.type() == QVariant::List) {
                QVariantList e = entity.toList();
                foreach (const QVariant &ee, e) {
                    QVariantMap eee = ee.toMap();
                    eee.insert("type", key);
                    entitiesSortedByIndices.append(eee);
                }
            } else {
                DEBUG() << entity;
            }
        }
        qSort(entitiesSortedByIndices.begin(), entitiesSortedByIndices.end(), &Status::indicesGreaterThan);
        QVariantList media;
        foreach (const QVariant &item, entitiesSortedByIndices) {
            QVariantMap entity = item.toMap();
            QVariantList indices = entity.value("indices").toList();
            int start = indices.first().toInt();
            int end = indices.last().toInt();
            QString type = entity.value("type").toString();
            QString plainTextAfter;
            QString richTextAfter;
            if (type == "urls") {
                if (entity.contains("display_url")) {
                    plainTextAfter = entity.value("display_url").toString();
                    richTextAfter = QString("<a class=\"link\" href=\"")
                            .append(entity.value("expanded_url").toString())
                            .append("\" title=\"")
                            .append(entity.value("url").toString())
                            .append("\">")
                            .append(entity.value("display_url").toString())
                            .append("</a>");
                } else {
                    plainTextAfter = entity.value("url").toString();
                    richTextAfter = QString("<a class=\"link\" href=\"")
                            .append(entity.value("url").toString())
                            .append("\" title=\"")
                            .append(entity.value("url").toString())
                            .append("\">")
                            .append(entity.value("url").toString())
                            .append("</a>");
                }
            } else if (type == "user_mentions") {
                richTextAfter = QString("<a class=\"screen_name\" href=\"user://%1\" title=\"@%2\">@%2</a>")
                        .arg(entity.value("id_str").toString())
                        .arg(entity.value("screen_name").toString());
            } else if (type == "hashtags") {
                richTextAfter = QString("<a class=\"hash_tag\" href=\"search://#%1\" title=\"#%2\">#%2</a>")
                        .arg(entity.value("text").toString())
                        .arg(entity.value("text").toString());
            } else if (type == "media") {
                plainTextAfter = entity.value("display_url").toString();
                richTextAfter = QString("<a class=\"media\" href=\"")
                        .append(entity.value("media_url").toString())
                        .append("\" title=\"")
                        .append(entity.value("url").toString())
                        .append("\">")
                        .append(entity.value("display_url").toString())
                        .append("</a>");
                media.append(entity.value("media_url"));
            } else {
                DEBUG() << type << item;
            }
            if (!plainTextAfter.isNull())
                plainText.replace(start, end - start, plainTextAfter);
            if (!richTextAfter.isNull())
                richText.replace(start, end - start, richTextAfter);
        }


//        DEBUG() << ret.value("text").toString();
        ret.insert("plain_text", escapeHtml(plainText));
//        DEBUG() << ret.value("plain_text").toString();
        ret.insert("rich_text", richText.replace("\n", "<br />").replace("\t", "&nbsp;").replace(QString::fromUtf8("　"), "&nbsp;&nbsp;&nbsp;&nbsp;"));
//        DEBUG() << ret.value("rich_text").toString();
        ret.insert("media", media);
    } else {
        DEBUG() << text;
        if (!ret.contains("plain_text"))
            ret.insert("plain_text", escapeHtml(text));
        if (!ret.contains("rich_text"))
            ret.insert("rich_text", text.replace(" ", "&nbsp;").replace("\n", "<br />").replace(QString::fromUtf8("　"), "&nbsp;&nbsp;&nbsp;&nbsp;"));
    }

    if (ret.contains("retweeted_status") && !ret.value("retweeted_status").isNull()) {
        ret.insert("retweeted_status", Status::parse(ret.value("retweeted_status").toMap()));
    }
    return ret;
}

#include "status.moc"
