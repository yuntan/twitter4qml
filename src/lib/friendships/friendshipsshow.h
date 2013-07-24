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

#ifndef FRIENDSHIPSSHOW_H
#define FRIENDSHIPSSHOW_H

#include "abstracttwitteraction.h"

class TWITTER4QML_EXPORT FriendshipsShow : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString source_id READ source_id WRITE source_id NOTIFY source_idChanged)
    Q_PROPERTY(QString source_screen_name READ source_screen_name WRITE source_screen_name NOTIFY source_screen_nameChanged)
    Q_PROPERTY(QString target_id READ target_id WRITE target_id NOTIFY target_idChanged)
    Q_PROPERTY(QString target_screen_name READ target_screen_name WRITE target_screen_name NOTIFY target_screen_nameChanged)
    Q_PROPERTY(QVariantMap relationship READ relationship WRITE relationship NOTIFY relationshipChanged DESIGNABLE false USER true)
public:
    explicit FriendshipsShow(QObject *parent = 0);

public slots:
    void exec();

signals:
    void source_idChanged(const QString &source_id);
    void source_screen_nameChanged(const QString &source_screen_name);
    void target_idChanged(const QString &target_id);
    void target_screen_nameChanged(const QString &target_screen_name);
    void relationshipChanged(const QVariantMap &relationship);

protected:
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/friendships/show.json"); }
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }

private:
    class Private;
    Private *d;

    ADD_PROPERTY(const QString &, source_id, QString)
    ADD_PROPERTY(const QString &, source_screen_name, QString)
    ADD_PROPERTY(const QString &, target_id, QString)
    ADD_PROPERTY(const QString &, target_screen_name, QString)
    ADD_PROPERTY(const QVariantMap &, relationship, QVariantMap)
};

#endif // FRIENDSHIPSSHOW_H
