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

#ifndef SEARCH_H
#define SEARCH_H

#include "../tools/abstracttwittermodel.h"

class Search : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(QString q READ q WRITE q NOTIFY qChanged)
    Q_PROPERTY(QString geocode READ geocode WRITE geocode NOTIFY geocodeChanged)
    Q_PROPERTY(QString lang READ lang WRITE lang NOTIFY langChanged)
    Q_PROPERTY(QString locale READ locale WRITE locale NOTIFY localeChanged)
    Q_PROPERTY(QString result_type READ result_type WRITE result_type NOTIFY result_typeChanged)
    Q_PROPERTY(int count READ count WRITE count NOTIFY countChanged)
    Q_PROPERTY(QString until READ until WRITE until NOTIFY untilChanged)
    Q_PROPERTY(QString since_id READ since_id WRITE since_id NOTIFY since_idChanged)
    Q_PROPERTY(QString max_id READ max_id WRITE max_id NOTIFY max_idChanged)
    Q_PROPERTY(bool include_entities READ include_entities WRITE include_entities NOTIFY include_entitiesChanged)

    Q_PROPERTY(QVariantMap search_metadata READ search_metadata WRITE search_metadata NOTIFY search_metadataChanged DESIGNABLE false)

public:
    enum Roles {
        created_at_role = Qt::UserRole + 1
        , FromUserRole
        , Fromuser_idRole
        , FromUsername_role
        , id_role
        , id_str_role
        , in_reply_to_status_idRole
        , IsoLanguagecode_role
        , MetadataRole
        , ProfileImageurl_role
        , ProfileImageUrlHttpsRole
        , SourceRole
        , TextRole
        , plain_textRole
        , ToUserRole
        , Touser_idRole
        , ToUsername_role
    };
    explicit Search(QObject *parent = 0);

    static QVariantMap parse(const QVariantMap &status);
    static bool indicesGreaterThan(const QVariant &v1, const QVariant &v2);

    DataManager::DataType dataType() const { return DataManager::SearchData; }

public slots:
    virtual void reload();

signals:
    void qChanged(const QString &q);
    void geocodeChanged(const QString &geocode);
    void langChanged(const QString &lang);
    void localeChanged(const QString &locale);
    void result_typeChanged(const QString &result_type);
    void countChanged(int count);
    void untilChanged(const QString &until);
    void since_idChanged(const QString &since_id);
    void max_idChanged(const QString &max_id);
    void include_entitiesChanged(bool include_entities);

    void search_metadataChanged(const QVariantMap &search_metadata);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/search/tweets.json"); }
    QString httpMethod() const { return "GET"; }
    void parseDone(const QVariant &result);
    void dataAdded(const QString &key, const QVariantMap &value);

private:
    Q_DISABLE_COPY(Search)

    ADD_PROPERTY(const QString &, q, QString)
    ADD_PROPERTY(const QString &, geocode, QString)
    ADD_PROPERTY(const QString &, lang, QString)
    ADD_PROPERTY(const QString &, locale, QString)
    ADD_PROPERTY(const QString &, result_type, QString)
    ADD_PROPERTY(int, count, int)
    ADD_PROPERTY(const QString &, until, QString)
    ADD_PROPERTY(const QString &, since_id, QString)
    ADD_PROPERTY(const QString &, max_id, QString)
    ADD_PROPERTY(bool, include_entities, bool)

    ADD_PROPERTY(const QVariantMap &, search_metadata, QVariantMap)
};

#endif // SEARCH_H
