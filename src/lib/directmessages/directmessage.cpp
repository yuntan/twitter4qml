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

#include "directmessage.h"
#include "showdirectmessages.h"
#include "newdirectmessages.h"
#include "destroydirectmessages.h"

#include "datamanager.h"
#include "user.h"

#include "utils.h"

#include <QtCore/QMetaProperty>

class DirectMessage::Private : public QObject
{
    Q_OBJECT
public:
    Private(DirectMessage *parent);

    bool loading;

    void create(const QVariantMap &parameters);
    void destroy();

private slots:
    void setLoading(bool loading);
    void id_strChanged(const QString &id_str);
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
    connect(q, SIGNAL(id_strChanged(QString)), this, SLOT(id_strChanged(QString)));
}

void DirectMessage::Private::setLoading(bool l)
{
    if (loading == l) return;
    loading = l;
    emit q->loadingChanged(l);
}

void DirectMessage::Private::id_strChanged(const QString &id)
{
    q->created_at(QString());
    q->entities(QVariantMap());
    q->recipient(QVariantMap());
    q->recipient_id(QString());
    q->recipient_screen_name(QString());
    q->sender(QVariantMap());
    q->sender_id(QString());
    q->sender_screen_name(QString());
    q->text(QString());
    q->plain_text(QString());
    q->rich_text(QString());
    q->media(QVariantList());
    if (id.isEmpty()) {
    } else {
        ShowDirectMessages *action = new ShowDirectMessages(this);
        action->id(id);
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
    NewDirectMessages *action = new NewDirectMessages(this);
    action->user_id(parameters.value("user_id").toString());
    action->text(parameters.value("text").toString());
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
    DestroyDirectMessages *action = new DestroyDirectMessages(this);
    action->id(q->id_str());
    action->include_entities(true);
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
    if (qobject_cast<DestroyDirectMessages *>(QObject::sender())) {
        DEBUG() << data;
        q->id_str(QString());
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
        DataManager::instance()->addData(DataManager::DirectMessageData, q->id_str(), directMessage);
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

void DirectMessage::newDirectMessages(QVariantMap parameters)
{
    d->create(parameters);
}

void DirectMessage::destroyDirectMessages()
{
    d->destroy();
}

bool DirectMessage::loading() const
{
    return d->loading;
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
        QString plain_text = text;
        QString rich_text = text.replace(" ", "\t");
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
            QString plain_textAfter;
            QString rich_textAfter;
            if (type == "urls") {
                if (entity.contains("display_url")) {
                    plain_textAfter = entity.value("display_url").toString();
                    rich_textAfter = QString("<a class=\"link\" href=\"")
                            .append(entity.value("expanded_url").toString())
                            .append("\" title=\"")
                            .append(entity.value("url").toString())
                            .append("\">")
                            .append(entity.value("display_url").toString())
                            .append("</a>");
                } else {
                    plain_textAfter = entity.value("url").toString();
                    rich_textAfter = QString("<a class=\"link\" href=\"")
                            .append(entity.value("url").toString())
                            .append("\" title=\"")
                            .append(entity.value("url").toString())
                            .append("\">")
                            .append(entity.value("url").toString())
                            .append("</a>");
                }
            } else if (type == "user_mentions") {
                rich_textAfter = QString("<a class=\"screen_name\" href=\"user://%1\" title=\"@%2\">@%2</a>")
                        .arg(entity.value("id_str").toString())
                        .arg(entity.value("screen_name").toString());
            } else if (type == "hashtags") {
                rich_textAfter = QString("<a class=\"hash_tag\" href=\"search://#%1\" title=\"#%2\">#%2</a>")
                        .arg(entity.value("text").toString())
                        .arg(entity.value("text").toString());
            } else if (type == "media") {
                plain_textAfter = entity.value("display_url").toString();
                rich_textAfter = QString("<a class=\"media\" href=\"")
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
            if (!plain_textAfter.isNull())
                plain_text.replace(start, end - start, plain_textAfter);
            if (!rich_textAfter.isNull())
                rich_text.replace(start, end - start, rich_textAfter);
        }
        ret.insert("plain_text", escapeHtml(plain_text));
        ret.insert("rich_text", rich_text.replace("\n", "<br />").replace("\t", "&nbsp;").replace(QString::fromUtf8("　"), "&nbsp;&nbsp;&nbsp;&nbsp;"));
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
