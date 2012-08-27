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

#include "listsmemberships.h"

ListsMemberships::ListsMemberships(QObject *parent)
    : AbstractListsModel(parent)
{
}

void ListsMemberships::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::Map) {
        QVariantMap object = result.toMap();
        if (object.contains("lists") && object.value("lists").type() == QVariant::List) {
            AbstractListsModel::parseDone(object.value("lists"));
        }
        if (object.contains("next_cursor"))
            setNextCursor(object.value("next_cursor").toInt());
        if (object.contains("next_cursor_str"))
            setNextCursorStr(object.value("next_cursor_str").toString());
        if (object.contains("previous_cursor"))
            setPreviousCursor(object.value("previous_cursor").toInt());
        if (object.contains("previous_cursor_str"))
            setPreviousCursorStr(object.value("previous_cursor_str").toString());
    }
}
