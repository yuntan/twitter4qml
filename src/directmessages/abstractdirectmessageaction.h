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

#ifndef ABSTRACTDIRECTMESSAGEACTION_H
#define ABSTRACTDIRECTMESSAGEACTION_H

#include "../tools/abstracttwitteraction.h"

class AbstractDirectMessageAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractDirectMessageAction)
public:
    explicit AbstractDirectMessageAction(QObject *parent = 0);
    ~AbstractDirectMessageAction();

    const QString &userId() const;
    void setUserId(const QString &userId);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    const QString &text() const;
    void setText(const QString &text);
    const QString &id() const;
    void setId(const QString &id);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void textChanged(const QString &text);
    void idChanged(const QString &id);
    void includeEntitiesChanged(bool includeEntities);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "POST"; }

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTDIRECTMESSAGEACTION_H
