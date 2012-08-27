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

#include "utils.h"
#include "twitter4qml.h"
#include <QtCore/QMap>
#include <QtCore/QRegExp>

QString escapeHtml(const QString &text)
{
    static QMap<QString, QString> table;
    if (table.isEmpty()) {
        table.insert("&quot;", "\"");
        table.insert("&apos;", "'");
        table.insert("&lsquo;", QString::fromUtf8("‘"));
        table.insert("&rsquo;", QString::fromUtf8("’"));
        table.insert("&ldquo;", QString::fromUtf8("“"));
        table.insert("&rdquo;", QString::fromUtf8("”"));
        table.insert("&yen;", QString::fromUtf8("¥"));
        table.insert("&gt;", ">");
        table.insert("&lt;", "<");
        table.insert("&mdash;", QString::fromUtf8("—"));
        table.insert("\r\n", "\n");
        table.insert("\r", "\n");
    }

    QString ret = text;
    foreach (const QString &from, table.keys()) {
        ret.replace(from, table[from]);
    }
    {
        QRegExp regexp("&#x([0-9a-f]+);");
        while (regexp.indexIn(ret) != -1) {
            ret.replace(regexp.cap(0), QChar(regexp.cap(1).toInt(0, 16)));
        }
    }
    {
        QRegExp regexp("&#([0-9]+);");
        while (regexp.indexIn(ret) != -1) {
            ret.replace(regexp.cap(0), QChar(regexp.cap(1).toInt()));
        }
    }

    ret.replace("&amp;", "&");

//    if (text != ret) {
//        DEBUG() << text;
//        DEBUG() << ret;
//    }
    return ret;
}
