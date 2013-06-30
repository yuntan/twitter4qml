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

#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "twitter4qml_global.h"

#define ADD_PROPERTY(type, name, type2) \
public: \
    type name() const { return m_##name; } \
    void name(type name) { \
        if (m_##name == name) return; \
        m_##name = name; \
        emit name##Changed(name); \
    } \
private: \
    type2 m_##name;

class TWITTER4QML_EXPORT DirectMessage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(QString created_at READ created_at WRITE created_at NOTIFY created_atChanged)
    Q_PROPERTY(QVariantMap entities READ entities WRITE entities NOTIFY entitiesChanged)
    Q_PROPERTY(QString id_str READ id_str WRITE id_str NOTIFY id_strChanged)
    Q_PROPERTY(QVariantMap recipient READ recipient WRITE recipient NOTIFY recipientChanged)
    Q_PROPERTY(QString recipient_id READ recipient_id WRITE recipient_id NOTIFY recipient_idChanged)
    Q_PROPERTY(QString recipient_screen_name READ recipient_screen_name WRITE recipient_screen_name NOTIFY recipient_screen_nameChanged)
    Q_PROPERTY(QVariantMap sender READ sender WRITE sender NOTIFY senderChanged)
    Q_PROPERTY(QString sender_id READ sender_id WRITE sender_id NOTIFY sender_idChanged)
    Q_PROPERTY(QString sender_screen_name READ sender_screen_name WRITE sender_screen_name NOTIFY sender_screen_nameChanged)
    Q_PROPERTY(QString text READ text WRITE text NOTIFY textChanged)
    Q_PROPERTY(QString plain_text READ plain_text WRITE plain_text NOTIFY plain_textChanged)
    Q_PROPERTY(QString rich_text READ rich_text WRITE rich_text NOTIFY rich_textChanged)
    Q_PROPERTY(QVariantList media READ media WRITE media NOTIFY mediaChanged)
    Q_PROPERTY(QVariantMap data READ data NOTIFY dataChanged DESIGNABLE false)
    Q_DISABLE_COPY(DirectMessage)
public:
    explicit DirectMessage(QObject *parent = 0);

    static QVariantMap parse(const QVariantMap &directMessage);
    static bool indicesGreaterThan(const QVariant &v1, const QVariant &v2);

    bool loading() const;
    QVariantMap data() const;

    Q_INVOKABLE void newDirectMessages(QVariantMap parameters);
    Q_INVOKABLE void destroyDirectMessages();

    Q_INVOKABLE void debug() const;

signals:
    void loadingChanged(bool loading);
    void created_atChanged(const QString &created_at);
    void entitiesChanged(const QVariantMap &entities);
    void id_strChanged(const QString &id_str);
    void recipientChanged(const QVariantMap &recipient);
    void recipient_idChanged(const QString &recipient_id);
    void recipient_screen_nameChanged(const QString &recipient_screen_name);
    void senderChanged(const QVariantMap &sender);
    void sender_idChanged(const QString &sender_id);
    void sender_screen_nameChanged(const QString &sender_screen_name);
    void textChanged(const QString &text);
    void plain_textChanged(const QString &plain_text);
    void rich_textChanged(const QString &rich_text);
    void mediaChanged(const QVariantList &media) const;
    void dataChanged();

private:
    class Private;
    Private *d;

    ADD_PROPERTY(const QString &, created_at, QString)
    ADD_PROPERTY(const QVariantMap &, entities, QVariantMap)
    ADD_PROPERTY(const QString &, id_str, QString)
    ADD_PROPERTY(const QVariantMap &, recipient, QVariantMap)
    ADD_PROPERTY(const QString &, recipient_id, QString)
    ADD_PROPERTY(const QString &, recipient_screen_name, QString)
    ADD_PROPERTY(const QVariantMap &, sender, QVariantMap)
    ADD_PROPERTY(const QString &, sender_id, QString)
    ADD_PROPERTY(const QString &, sender_screen_name, QString)
    ADD_PROPERTY(const QString &, text, QString)
    ADD_PROPERTY(const QString &, plain_text, QString)
    ADD_PROPERTY(const QString &, rich_text, QString)
    ADD_PROPERTY(const QVariantList &, media, QVariantList)
};

#endif // DIRECTMESSAGE_H
