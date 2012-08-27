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

#ifndef LISTSTATUSES_H
#define LISTSTATUSES_H

#include "../statuses/abstractstatusesmodel.h"

class ListStatuses : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ listId WRITE setListId NOTIFY listIdChanged)
    Q_PROPERTY(QString since_id READ sinceId WRITE setSinceId NOTIFY sinceIdChanged)
    Q_PROPERTY(QString max_id READ maxId WRITE setMaxId NOTIFY maxIdChanged)
    Q_PROPERTY(int per_page READ perPage WRITE setPerPage NOTIFY perPageChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(bool include_rts READ includeRts WRITE setIncludeRts NOTIFY includeRtsChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_DISABLE_COPY(ListStatuses)
public:
    explicit ListStatuses(QObject *parent = 0);

signals:
    void listIdChanged(const QString &listId);
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void pageChanged(int page);
    void perPageChanged(int perPage);
    void includeRtsChanged(bool includeRts);
    void includeEntitiesChanged(bool includeEntities);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/statuses.json"); }
};

#endif // LISTSTATUSES_H
