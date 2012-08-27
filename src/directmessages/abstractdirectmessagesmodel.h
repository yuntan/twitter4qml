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

#ifndef ABSTRACTDIRECTMESSAGESMODEL_H
#define ABSTRACTDIRECTMESSAGESMODEL_H

#include "../tools/abstracttwittermodel.h"

class AbstractDirectMessagesModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractDirectMessagesModel)
public:
    enum Roles {
        CreatedAtRole = Qt::UserRole + 1
        , EntitiesRole
        , IdRole
        , IdStrRole
        , RecipientRole
        , RecipientIdRole
        , RecipientScreenNameRole
        , SenderRole
        , SenderIdRole
        , SenderScreenNameRole
        , TextRole
        , PlainTextRole
        , RichTextRole
    };
    explicit AbstractDirectMessagesModel(QObject *parent = 0);
    ~AbstractDirectMessagesModel();

    const QString &sinceId() const;
    void setSinceId(const QString &sinceId);
    const QString &maxId() const;
    void setMaxId(const QString &maxId);
    int count() const;
    void setCount(int count);
    int page() const;
    void setPage(int page);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);

    DataManager::DataType dataType() const { return DataManager::DirectMessageData; }

signals:
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void countChanged(int count);
    void pageChanged(int page);
    void includeEntitiesChanged(bool includeEntities);

protected:
    AuthorizeBy authenticationMethod() const;
    QString httpMethod() const;
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTDIRECTMESSAGESMODEL_H
