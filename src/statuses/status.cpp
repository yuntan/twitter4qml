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

    void update(const QVariantMap &parameters);
    void retweet(const QVariantMap &parameters);
    void destroy();
    void favorite();
    void unfavorite();

private slots:
    void id_strChanged(const QString &id_str);
    void dataChanged(const QVariant &data);

private:
    Status *q;
    QList<AbstractTwitterAction *> tasks;
};

Status::Private::Private(Status *parent)
    : QObject(parent)
    , q(parent)
{
    connect(q, SIGNAL(id_strChanged(QString)), this, SLOT(id_strChanged(QString)));
}

void Status::Private::id_strChanged(const QString &id)
{
    q->contributors(QVariantList());
    q->contributors(QVariantList());
    q->coordinates(QVariantMap());
    q->entities(QVariantMap());
    q->favorited(false);
    q->geo(QVariantMap());
    q->in_reply_to_screen_name(QString());
    q->in_reply_to_status_id_str(QString());
    q->in_reply_to_user_id_str(QString());
    q->place(QVariantMap());
    q->possibly_sensitive(false);
    q->retweet_count(0);
    q->retweeted(false);
    q->retweeted_status(QVariantMap());
    q->source(QString());
    q->text(QString());
    q->plain_text(QString());
    q->rich_text(QString());
    q->truncated(false);
    q->user(QVariantMap());
    q->media(QVariantList());

    if (id.isEmpty()) {
    } else {
        ShowStatus *action = new ShowStatus(this);
        action->id(id);
        connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
        if (q->m_loading) {
            tasks.append(action);
        } else {
            q->loading(true);
            action->exec();
        }
    }
}

void Status::Private::update(const QVariantMap &parameters)
{
    AbstractTwitterAction *action = 0;
    if (parameters.contains("media") && !parameters.value("media").toList().isEmpty()) {
        UpdateStatusWithMedia *act = new UpdateStatusWithMedia(this);
        act->status(parameters.value("status").toString());
        act->latitude(parameters.value("_lat").toDouble());
        act->longitude(parameters.value("_long").toDouble());
        act->place_id(parameters.value("place_id").toString());
        act->media(parameters.value("media").toList());
        act->in_reply_to_status_id(parameters.value("in_reply_to_status_id").toString());
        act->trim_user(false);
        act->include_entities(true);
        connect(act, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
        action = act;
    } else {
        UpdateStatus *act = new UpdateStatus(this);
        act->status(parameters.value("status").toString());
        act->latitude(parameters.value("_lat").toDouble());
        act->longitude(parameters.value("_long").toDouble());
        act->place_id(parameters.value("place_id").toString());
        act->in_reply_to_status_id(parameters.value("in_reply_to_status_id").toString());
        act->trim_user(false);
        act->include_entities(true);
        connect(act, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
        action = act;
    }
    if (q->loading()) {
        tasks.append(action);
    } else {
       q->loading(true);
       action->exec();
    }
}

void Status::Private::retweet(const QVariantMap &parameters)
{
    RetweetStatus *action = new RetweetStatus(this);
    action->id(parameters.value("id").toString());
    action->trim_user(true);
    action->include_entities(true);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (q->loading()) {
        tasks.append(action);
    } else {
       q->loading(true);
       action->exec();
    }
}

void Status::Private::destroy()
{
    DestroyStatus *action = new DestroyStatus(this);
    action->id(q->m_id_str);
    action->include_entities(true);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (q->loading()) {
        tasks.append(action);
    } else {
       q->loading(true);
       action->exec();
    }
}

void Status::Private::favorite()
{
    AbstractFavoriteAction *action = new CreateFavorite(this);
    action->id(q->m_id_str);
    action->include_entities(true);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (q->loading()) {
        tasks.append(action);
    } else {
       q->loading(true);
       action->exec();
    }
}

void Status::Private::unfavorite()
{
    AbstractFavoriteAction *action = new DestroyFavorite(this);
    action->id(q->m_id_str);
    action->include_entities(true);
    connect(action, SIGNAL(dataChanged(QVariant)), this, SLOT(dataChanged(QVariant)));
    if (q->loading()) {
        tasks.append(action);
    } else {
       q->loading(true);
       action->exec();
    }
}

void Status::Private::dataChanged(const QVariant &data)
{
    if (qobject_cast<DestroyStatus *>(sender())) {
        DEBUG() << data;
        q->id_str(QString());
        emit q->dataChanged();
        qDeleteAll(tasks);
        tasks.clear();
        q->loading(false);
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
                q->setProperty(key, status.value(key));
            } else {
                q->setProperty(key, QVariant());
            }
        }
        if (!qobject_cast<RetweetStatus *>(action)) {
            DataManager::instance()->addData(DataManager::StatusData, q->id_str(), status);
        }
        emit q->dataChanged();
        action->deleteLater();
    }
    if (tasks.isEmpty()) {
        q->loading(false);
    } else {
        tasks.takeFirst()->exec();
    }
}


Status::Status(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
    , m_loading(false)
    , m_favorited(false)
    , m_possibly_sensitive(false)
    , m_retweet_count(0)
    , m_retweeted(false)
    , m_truncated(false)
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
        qSort(entitiesSortedByIndices.begin(), entitiesSortedByIndices.end(), &Status::indicesGreaterThan);
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


//        DEBUG() << ret.value("text").toString();
        ret.insert("plain_text", escapeHtml(plain_text));
//        DEBUG() << ret.value("plain_text").toString();
        ret.insert("rich_text", rich_text.replace("\n", "<br />").replace("\t", "&nbsp;").replace(QString::fromUtf8("　"), "&nbsp;&nbsp;&nbsp;&nbsp;"));
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
