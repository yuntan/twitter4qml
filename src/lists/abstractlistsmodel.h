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

#ifndef ABSTRACTLISTSMODEL_H
#define ABSTRACTLISTSMODEL_H

#include "../tools/abstracttwittermodel.h"

class AbstractListsModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractListsModel)

public:
    enum Roles {
        CreatedAtRole = Qt::UserRole + 1
        , DescriptionRole
        , FollowingRole
        , FullNameRole
        , IdRole
        , IdStrRole
        , MemberCountRole
        , ModeRole
        , NameRole
        , SlugRole
        , SubscriberCountRole
        , UriRole
        , UserRole
    };

    explicit AbstractListsModel(QObject *parent = 0);
    ~AbstractListsModel();

    const QString &userId() const;
    void setUserId(const QString &userId);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    int count() const;
    void setCount(int count);
    const QString &cursor() const;
    void setCursor(const QString &cursor);

    int nextCursor() const;
    void setNextCursor(int nextCursor);
    const QString &nextCursorStr() const;
    void setNextCursorStr(const QString &nextCursorStr);
    int previousCursor() const;
    void setPreviousCursor(int previousCursor);
    const QString &previousCursorStr() const;
    void setPreviousCursorStr(const QString &previousCursorStr);

    DataManager::DataType dataType() const { return DataManager::ListData; }

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void countChanged(int count);
    void cursorChanged(const QString &cursor);

    void nextCursorChanged(int nextCursor) const;
    void nextCursorStrChanged(const QString &nextCursorStr) const;
    void previousCursorChanged(int previousCursor) const;
    void previousCursorStrChanged(const QString &previousCursorStr) const;

protected:
    AuthorizeBy authenticationMethod() const;
    QString httpMethod() const;
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTLISTSMODEL_H
