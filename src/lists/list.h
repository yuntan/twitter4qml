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

#ifndef LIST_H
#define LIST_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "twitter4qml_global.h"

class List : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(QString created_at READ created_at WRITE created_at NOTIFY created_atChanged)
    Q_PROPERTY(QString description READ description WRITE description NOTIFY descriptionChanged)
    Q_PROPERTY(bool following READ following WRITE following NOTIFY followingChanged)
    Q_PROPERTY(QString full_name READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString id_str READ id_str WRITE id_str NOTIFY id_strChanged)
    Q_PROPERTY(int member_count READ memberCount WRITE setMemberCount NOTIFY memberCountChanged)
    Q_PROPERTY(QString mode READ mode WRITE mode NOTIFY modeChanged)
    Q_PROPERTY(QString name READ name WRITE name NOTIFY nameChanged)
    Q_PROPERTY(QString slug READ slug WRITE slug NOTIFY slugChanged)
    Q_PROPERTY(int subscriber_count READ subscriberCount WRITE setSubscriberCount NOTIFY subscriberCountChanged)
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)
    Q_PROPERTY(QVariantMap user READ user WRITE user NOTIFY userChanged)

    Q_DISABLE_COPY(List)
public:
    explicit List(QObject *parent = 0);

    static QVariantMap parse(const QVariantMap &status);

    bool loading() const;
    const QString &created_at() const;
    const QString &description() const;
    bool following() const;
    const QString &fullName() const;
    const QString &id_str() const;
    int memberCount() const;
    const QString &mode() const;
    const QString &name() const;
    const QString &slug() const;
    int subscriberCount() const;
    const QString &uri() const;
    const QVariantMap &user() const;

    QVariantMap data() const;

    Q_INVOKABLE void createList(QVariantMap parameters);
    Q_INVOKABLE void updateList(QVariantMap parameters);
    Q_INVOKABLE void destroyList();
    Q_INVOKABLE void subscribe();
    Q_INVOKABLE void unsubscribe();

    Q_INVOKABLE void debug() const;

public slots:
    void created_at(const QString &created_at);
    void description(const QString &description);
    void following(bool following);
    void setFullName(const QString &fullName);
    void id_str(const QString &id_str);
    void setMemberCount(int memberCount);
    void mode(const QString &mode);
    void name(const QString &name);
    void slug(const QString &slug);
    void setSubscriberCount(int subscriberCount);
    void setUri(const QString &uri);
    void user(const QVariantMap &user);

signals:
    void loadingChanged(bool loading);
    void created_atChanged(const QString &created_at);
    void descriptionChanged(const QString &description);
    void followingChanged(bool following);
    void fullNameChanged(const QString &fullName);
    void id_strChanged(const QString &id_str);
    void memberCountChanged(int memberCount);
    void modeChanged(const QString &mode);
    void nameChanged(const QString &name);
    void slugChanged(const QString &slug);
    void subscriberCountChanged(int subscriberCount);
    void uriChanged(const QString &uri);
    void userChanged(const QVariantMap &user);
    void dataChanged();

private:
    class Private;
    Private *d;
};

#endif // LIST_H
