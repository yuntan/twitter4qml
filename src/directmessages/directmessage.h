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

#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "twitter4qml_global.h"

class DirectMessage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(QString created_at READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QVariantMap entities READ entities WRITE setEntities NOTIFY entitiesChanged)
    Q_PROPERTY(QString id_str READ idStr WRITE setIdStr NOTIFY idStrChanged)
    Q_PROPERTY(QVariantMap recipient READ recipient WRITE setRecipient NOTIFY recipientChanged)
    Q_PROPERTY(QString recipient_id READ recipientId WRITE setRecipientId NOTIFY recipientIdChanged)
    Q_PROPERTY(QString recipient_screen_name READ recipientScreenName WRITE setRecipientScreenName NOTIFY recipientScreenNameChanged)
    Q_PROPERTY(QVariantMap sender READ sender WRITE setSender NOTIFY senderChanged)
    Q_PROPERTY(QString sender_id READ senderId WRITE setSenderId NOTIFY senderIdChanged)
    Q_PROPERTY(QString sender_screen_name READ senderScreenName WRITE setSenderScreenName NOTIFY senderScreenNameChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString plain_text READ plainText WRITE setPlainText NOTIFY plainTextChanged)
    Q_PROPERTY(QString rich_text READ richText WRITE setRichText NOTIFY richTextChanged)
    Q_PROPERTY(QVariantList media READ media WRITE setMedia NOTIFY mediaChanged)
    Q_PROPERTY(QVariantMap data READ data NOTIFY dataChanged DESIGNABLE false)
    Q_DISABLE_COPY(DirectMessage)
public:
    explicit DirectMessage(QObject *parent = 0);

    static QVariantMap parse(const QVariantMap &directMessage);
    static bool indicesGreaterThan(const QVariant &v1, const QVariant &v2);

    bool loading() const;
    const QString &createdAt() const;
    const QVariantMap &entities() const;
    const QString &idStr() const;
    const QVariantMap &recipient() const;
    const QString &recipientId() const;
    const QString &recipientScreenName() const;
    const QVariantMap &sender() const;
    const QString &senderId() const;
    const QString &senderScreenName() const;
    const QString &text() const;
    const QString &plainText() const;
    const QString &richText() const;
    const QVariantList &media() const;
    QVariantMap data() const;

    Q_INVOKABLE void newDirectMessage(QVariantMap parameters);
    Q_INVOKABLE void destroyDirectMessage();

    Q_INVOKABLE void debug() const;

public slots:
    void setCreatedAt(const QString &createdAt);
    void setEntities(const QVariantMap &entities);
    void setIdStr(const QString &idStr);
    void setRecipient(const QVariantMap &recipient);
    void setRecipientId(const QString &recipientId);
    void setRecipientScreenName(const QString &recipientScreenName);
    void setSender(const QVariantMap &sender);
    void setSenderId(const QString &senderId);
    void setSenderScreenName(const QString &senderScreenName);
    void setText(const QString &text);
    void setPlainText(const QString &plainText);
    void setRichText(const QString &richText);
    void setMedia(const QVariantList &media);

signals:
    void loadingChanged(bool loading);
    void createdAtChanged(const QString &createdAt);
    void entitiesChanged(const QVariantMap &entities);
    void idStrChanged(const QString &idStr);
    void recipientChanged(const QVariantMap &recipient);
    void recipientIdChanged(const QString &recipientId);
    void recipientScreenNameChanged(const QString &recipientScreenName);
    void senderChanged(const QVariantMap &sender);
    void senderIdChanged(const QString &senderId);
    void senderScreenNameChanged(const QString &senderScreenName);
    void textChanged(const QString &text);
    void plainTextChanged(const QString &plainText);
    void richTextChanged(const QString &richText);
    void mediaChanged(const QVariantList &media) const;
    void dataChanged();

private:
    class Private;
    Private *d;
};

#endif // DIRECTMESSAGE_H
