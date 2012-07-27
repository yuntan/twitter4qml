#include "directmessage.h"
#include "showdirectmessage.h"
#include "newdirectmessage.h"
#include "destroydirectmessage.h"

#include "../tools/datamanager.h"
#include "../users/user.h"

#include "../utils.h"

#include <QtCore/QMetaProperty>

class DirectMessage::Private : public QObject
{
    Q_OBJECT
public:
    Private(DirectMessage *parent);

    bool loading;
    QString createdAt;
    QVariantMap entities;
    QString idStr;
    QVariantMap recipient;
    QString recipientId;
    QString recipientScreenName;
    QVariantMap sender;
    QString senderId;
    QString senderScreenName;
    QString text;
    QString plainText;
    QString richText;
    QVariantList media;

    void create(const QVariantMap &parameters);
    void destroy();

private slots:
    void setLoading(bool loading);
    void idStrChanged(const QString &idStr);
    void dataChanged(const QVariant &data);

private:
    DirectMessage *q;
    QList<AbstractTwitterAction *> tasks;
};

DirectMessage::Private::Private(DirectMessage *parent)
    : QObject(parent)
    , loading(false)
    , q(parent)
{
    connect(q, SIGNAL(idStrChanged(QString)), this, SLOT(idStrChanged(QString)));
}

void DirectMessage::Private::setLoading(bool l)
{
    if (loading == l) return;
    loading = l;
    emit q->loadingChanged(l);
}

void DirectMessage::Private::idStrChanged(const QString &id)
{
    createdAt.clear();
    entities.clear();
    recipient.clear();
    recipientId.clear();
    recipientScreenName.clear();
    sender.clear();
    senderId.clear();
    senderScreenName.clear();
    text.clear();
    plainText.clear();
    richText.clear();
    media.clear();
    if (id.isEmpty()) {
    } else {
        ShowDirectMessage *action = new ShowDirectMessage(this);
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

void DirectMessage::Private::create(const QVariantMap &parameters)
{
    NewDirectMessage *action = new NewDirectMessage(this);
    action->setUserId(parameters.value("user_id").toString());
    action->setText(parameters.value("text").toString());
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (loading) {
        tasks.append(action);
    } else {
       setLoading(true);
       action->exec();
    }
}

void DirectMessage::Private::destroy()
{
    DestroyDirectMessage *action = new DestroyDirectMessage(this);
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

void DirectMessage::Private::dataChanged(const QVariant &data)
{
    if (qobject_cast<DestroyDirectMessage *>(QObject::sender())) {
        DEBUG() << data;
        q->setIdStr(QString());
        emit q->dataChanged();
        qDeleteAll(tasks);
        tasks.clear();
        setLoading(false);
    }
    AbstractTwitterAction *action = qobject_cast<AbstractTwitterAction *>(QObject::sender());
    if (action) {
        QVariantMap directMessage = DirectMessage::parse(data.toMap());
        const QMetaObject *mo = q->metaObject();
        for (int i = 0; i < mo->propertyCount(); i++) {
            QMetaProperty prop = mo->property(i);
            if (!prop.isDesignable()) continue;
            const char *key = prop.name();
            if (directMessage.contains(key)) {
                q->setProperty(key, directMessage.value(key));
            } else {
                q->setProperty(key, QVariant());
            }
        }
        DataManager::instance()->addData(DataManager::DirectMessageData, q->idStr(), directMessage);
        emit q->dataChanged();
        action->deleteLater();
    }
    if (tasks.isEmpty()) {
        setLoading(false);
    } else {
        tasks.takeFirst()->exec();
    }
}


DirectMessage::DirectMessage(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

void DirectMessage::newDirectMessage(QVariantMap parameters)
{
    d->create(parameters);
}

void DirectMessage::destroyDirectMessage()
{
    d->destroy();
}

bool DirectMessage::loading() const
{
    return d->loading;
}

const QString &DirectMessage::createdAt() const
{
    return d->createdAt;
}

void DirectMessage::setCreatedAt(const QString &createdAt)
{
    if (d->createdAt == createdAt) return;
    d->createdAt = createdAt;
    emit createdAtChanged(createdAt);
}

const QVariantMap &DirectMessage::entities() const
{
    return d->entities;
}

void DirectMessage::setEntities(const QVariantMap &entities)
{
    if (d->entities == entities) return;
    d->entities = entities;
    emit entitiesChanged(entities);
}

const QString &DirectMessage::idStr() const
{
    return d->idStr;
}

void DirectMessage::setIdStr(const QString &idStr)
{
    if (d->idStr == idStr) return;
    d->idStr = idStr;
    emit idStrChanged(idStr);
}

const QVariantMap &DirectMessage::recipient() const
{
    return d->recipient;
}

void DirectMessage::setRecipient(const QVariantMap &recipient)
{
    if (d->recipient == recipient) return;
    d->recipient = recipient;
    emit recipientChanged(recipient);
}

const QString &DirectMessage::recipientId() const
{
    return d->recipientId;
}

void DirectMessage::setRecipientId(const QString &recipientId)
{
    if (d->recipientId == recipientId) return;
    d->recipientId = recipientId;
    emit recipientIdChanged(recipientId);
}

const QString &DirectMessage::recipientScreenName() const
{
    return d->recipientScreenName;
}

void DirectMessage::setRecipientScreenName(const QString &recipientScreenName)
{
    if (d->recipientScreenName == recipientScreenName) return;
    d->recipientScreenName = recipientScreenName;
    emit recipientScreenNameChanged(recipientScreenName);
}

const QVariantMap &DirectMessage::sender() const
{
    return d->sender;
}

void DirectMessage::setSender(const QVariantMap &sender)
{
    if (d->sender == sender) return;
    d->sender = sender;
    emit senderChanged(sender);
}

const QString &DirectMessage::senderId() const
{
    return d->senderId;
}

void DirectMessage::setSenderId(const QString &senderId)
{
    if (d->senderId == senderId) return;
    d->senderId = senderId;
    emit senderIdChanged(senderId);
}

const QString &DirectMessage::senderScreenName() const
{
    return d->senderScreenName;
}

void DirectMessage::setSenderScreenName(const QString &senderScreenName)
{
    if (d->senderScreenName == senderScreenName) return;
    d->senderScreenName = senderScreenName;
    emit senderScreenNameChanged(senderScreenName);
}

const QString &DirectMessage::text() const
{
    return d->text;
}

void DirectMessage::setText(const QString &text)
{
    if (d->text == text) return;
    d->text = text;
    emit textChanged(text);
}

const QString &DirectMessage::plainText() const
{
    return d->plainText;
}

void DirectMessage::setPlainText(const QString &plainText)
{
    if (d->plainText == plainText) return;
    d->plainText = plainText;
    emit plainTextChanged(plainText);
}

const QString &DirectMessage::richText() const
{
    return d->richText;
}

void DirectMessage::setRichText(const QString &richText)
{
    if (d->richText == richText) return;
    d->richText = richText;
    emit richTextChanged(richText);
}

const QVariantList &DirectMessage::media() const
{
    return d->media;
}

void DirectMessage::setMedia(const QVariantList &media)
{
    if (d->media == media) return;
    d->media = media;
    emit mediaChanged(media);
}

QVariantMap DirectMessage::data() const
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

bool DirectMessage::indicesGreaterThan(const QVariant &v1, const QVariant &v2)
{
    return v1.toMap().value("indices").toList().first().toInt() > v2.toMap().value("indices").toList().first().toInt();
}

void DirectMessage::debug() const
{
    const QMetaObject *mo = metaObject();
    for (int i = 0; i < mo->propertyCount(); i++) {
        QMetaProperty prop = mo->property(i);
        if (!prop.isDesignable()) continue;
        const char *key = prop.name();
        DEBUG() << key << property(key);
    }
}

QVariantMap DirectMessage::parse(const QVariantMap &directMessage)
{
    QVariantMap ret = directMessage;

    ret.insert("recipient", User::parse(ret.value("recipient").toMap()));
    ret.insert("sender", User::parse(ret.value("sender").toMap()));

    QString text = ret.value("text").toString();
    if (ret.contains("entities") && !ret.value("entities").isNull()) {
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
        qSort(entitiesSortedByIndices.begin(), entitiesSortedByIndices.end(), &DirectMessage::indicesGreaterThan);
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
                    richTextAfter = QString("<a class=\"link\" href=\"%1\" title=\"%2\">%3</a>")
                            .arg(entity.value("expanded_url").toString())
                            .arg(entity.value("url").toString())
                            .arg(entity.value("display_url").toString());
                } else {
                    plainTextAfter = entity.value("url").toString();
                    richTextAfter = QString("<a class=\"link\" href=\"%1\" title=\"%1\">%1</a>")
                            .arg(entity.value("url").toString());
                }
            } else if (type == "user_mentions") {
                richTextAfter = QString("<a class=\"screen_name\" href=\"user//:%1\" title=\"@%2\">@%2</a>")
                        .arg(entity.value("id_str").toString())
                        .arg(entity.value("screen_name").toString());
            } else if (type == "hashtags") {
                richTextAfter = QString("<a class=\"hash_tag\" href=\"search://#%1\" title=\"#%2\">#%2</a>")
                        .arg(entity.value("text").toString())
                        .arg(entity.value("text").toString());
            } else if (type == "media") {
                plainTextAfter = entity.value("display_url").toString();
                richTextAfter = QString("<a class=\"media\" href=\"%1\" title=\"%2\">%3</a>")
                        .arg(entity.value("media_url").toString())
                        .arg(entity.value("url").toString())
                        .arg(entity.value("display_url").toString());
                media.append(entity.value("media_url"));
            } else {
                DEBUG() << type << item;
            }
            if (!plainTextAfter.isNull())
                plainText.replace(start, end - start, plainTextAfter);
            if (!richTextAfter.isNull())
                richText.replace(start, end - start, richTextAfter);
        }
        ret.insert("plain_text", escapeHtml(plainText));
        ret.insert("rich_text", richText.replace("\n", "<br />").replace("\t", "&nbsp;").replace(QString::fromUtf8("　"), "&nbsp;&nbsp;&nbsp;&nbsp;"));
        ret.insert("media", media);
    } else {
        DEBUG() << text;
        if (!ret.contains("plain_text"))
            ret.insert("plain_text", escapeHtml(text));
        if (!ret.contains("rich_text"))
            ret.insert("rich_text", text.replace(" ", "&nbsp;").replace("\n", "<br />").replace(QString::fromUtf8("　"), "&nbsp;&nbsp;&nbsp;&nbsp;"));
    }
    return ret;
}

#include "directmessage.moc"
