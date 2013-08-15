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

#ifndef STATUSESSHOW_H
#define STATUSESSHOW_H

#include "abstractstatusaction.h"

class StatusesShow : public AbstractStatusAction
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE id NOTIFY idChanged)
    Q_PROPERTY(bool trim_user READ trim_user WRITE trim_user NOTIFY trim_userChanged)
    Q_PROPERTY(bool include_my_retweet READ include_my_retweet WRITE include_my_retweet NOTIFY include_my_retweetChanged)
    Q_PROPERTY(bool include_entities READ include_entities WRITE include_entities NOTIFY include_entitiesChanged)
    Q_DISABLE_COPY(StatusesShow)
public:
    explicit StatusesShow(QObject *parent = 0);

public slots:
    void exec();

signals:
    void idChanged(const QString &id);
    void trim_userChanged(bool trim_user);
    void include_my_retweetChanged(bool include_my_retweet);
    void include_entitiesChanged(bool include_entities);

protected:
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/statuses/show.json"); }
    QString httpMethod() const { return "GET"; }

    ADD_PROPERTY(bool, include_my_retweet, bool)
};

#endif // STATUSESSHOW_H
