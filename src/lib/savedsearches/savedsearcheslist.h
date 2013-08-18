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

#ifndef SAVEDSEARCHESLIST_H
#define SAVEDSEARCHESLIST_H

#include "abstracttwittermodel.h"

class TWITTER4QML_EXPORT SavedSearchesList : public AbstractTwitterModel
{
    Q_OBJECT
public:
    enum Roles {
        created_at_role = Qt::UserRole + 1
        , id_role
        , id_str_role
        , name_role
        , position_role
        , query_role
    };
    explicit SavedSearchesList(QObject *parent = 0);

    Q_INVOKABLE void savedSearchesCreate(QVariantMap parameters);
    Q_INVOKABLE void savedSearchesDestroy(QVariantMap parameters);

    bool isLoading() const;
    DataManager::DataType dataType() const { return DataManager::SavedSearchData; }

protected:
    virtual AuthorizeBy authenticationMethod() const { return AuthorizeByHeader; }
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/saved_searches/list.json"); }
    QString httpMethod() const { return "GET"; }
    void parseDone(const QVariant &result);

    void dataAdded(const QString &key, const QVariantMap &value);
    void dataAboutToBeRemoved(const QString &key, const QVariantMap &value);

private:
    Q_DISABLE_COPY(SavedSearchesList)
    class Private;
    Private *d;
};

#endif // SAVEDSEARCHESLIST_H
