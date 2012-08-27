/* Copyright (c) 2012 Twitter4QML Project.
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

#include "showrelatedresults.h"
#include "../statuses/status.h"

ShowRelatedResults::ShowRelatedResults(QObject *parent)
    : AbstractStatusesModel(parent)
{
}

static void qvariant_debug(const QVariant &value, int level = 0, QString prefix = QString())
{
    QVariantList list;
    QVariantMap map;
    switch (value.type()) {
    case QVariant::List:
        list = value.toList();
        foreach (const QVariant &v, list) {
            qvariant_debug(v, level + 1, prefix);
        }
        break;
    case QVariant::Map:
        map = value.toMap();
        foreach (const QString &key, map.keys()) {
            qvariant_debug(map[key], level + 1, key);
        }
        break;
    default:
        qDebug() << QString(level * 2, ' ') << prefix << value;
    }
}

void ShowRelatedResults::parseDone(const QVariant &result)
{
    if (result.type() != QVariant::List) {
        DEBUG();
        qvariant_debug(result);
        DEBUG();
        return;
    }
    QVariantList list = result.toList();
    if (list.isEmpty())
        return;
    if (list.length() > 1) {
        DEBUG();
        qvariant_debug(result);
        DEBUG();
        return;
    }
    QVariantMap map = list.first().toMap();
    if (map.value("groupName").toString() != "TweetsWithConversation" || map.value("resultType").toString() != "Tweet") {
        DEBUG();
        qvariant_debug(map);
        DEBUG();
        return;
    }
    if (map.value("results").type() != QVariant::List) {
        DEBUG();
        qvariant_debug(map);
        DEBUG();
        return;
    }
    QVariantList results = map.value("results").toList();
    foreach (const QVariant &v1, results) {
        QVariantMap result = v1.toMap();
        DEBUG() << result.value("annotations");
        if (result.value("kind").toString() != "Tweet" || result.value("score").toInt() != 1) {
            DEBUG();
            qvariant_debug(result);
            DEBUG();
            return;
        }
        QVariantMap value = result.value("value").toMap();
        addData(Status::parse(value));
    }
}
