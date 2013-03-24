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

#include "search.h"
#include "showstatus.h"
#include "status.h"
#include "../utils.h"
#include <QtCore/QQueue>

Search::Search(QObject *parent)
    : AbstractStatusesModel(parent)
    , m_result_type("mixed")
    , m_count(0)
    , m_include_entities(true)
{
}

void Search::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::Map) {
        QVariantMap object = result.toMap();
        if (object.contains("search_metadata"))
            search_metadata(object.value("search_metadata").toMap());
//        if (object.contains("query"))
//            setQ(object.value("query").toString());
        if (object.contains("statuses") && object.value("statuses").type() == QVariant::List) {
            QVariantList results = object.value("statuses").toList();
            if (results.isEmpty()) {
                emit loadingChanged(false);
            } else {
                foreach (const QVariant &result, results) {
                    if (result.type() == QVariant::Map) {
                        QVariantMap map = Search::parse(result.toMap());
                        addData(map);
                    }
                }
            }
        } else {
            DEBUG() << object;
        }
    }
}

void Search::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (value.value("text").toString().contains(QString(QByteArray::fromPercentEncoding(q().toUtf8())), Qt::CaseInsensitive)) {
        addData(value);
    }
}

bool Search::indicesGreaterThan(const QVariant &v1, const QVariant &v2)
{
    return v1.toMap().value("indices").toList().first().toInt() > v2.toMap().value("indices").toList().first().toInt();
}

QVariantMap Search::parse(const QVariantMap &status)
{
    QVariantMap ret = status;

    QString source = ret.value("source").toString();
    source.replace("&lt;", "<").replace("&gt;", ">").replace("&quat;", "\"");
    ret.insert("source", source);

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
        qSort(entitiesSortedByIndices.begin(), entitiesSortedByIndices.end(), &Search::indicesGreaterThan);
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

    return ret;
}
