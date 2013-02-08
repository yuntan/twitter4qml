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

#ifndef GEOSEARCH_H
#define GEOSEARCH_H

#include "../tools/abstracttwittermodel.h"

class GeoSearch : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(double _lat READ latitude WRITE latitude NOTIFY latitudeChanged)
    Q_PROPERTY(double _long READ longitude WRITE longitude NOTIFY longitudeChanged)
    Q_PROPERTY(QString query READ query WRITE query NOTIFY queryChanged)
    Q_PROPERTY(QString ip READ ip WRITE ip NOTIFY ipChanged)
    Q_PROPERTY(QString granularity READ granularity WRITE granularity NOTIFY granularityChanged)
    Q_PROPERTY(QString accuracy READ accuracy WRITE accuracy NOTIFY accuracyChanged)
    Q_PROPERTY(int max_results READ max_results WRITE max_results NOTIFY max_resultsChanged)
    Q_PROPERTY(QString contained_within READ contained_within WRITE contained_within NOTIFY contained_withinChanged)
    Q_DISABLE_COPY(GeoSearch)
public:
    enum Roles {
        AttrubutesRole = Qt::UserRole + 1
        , bounding_box_role
        , contained_within_role
        , country_role
        , country_code_role
        , full_name_role
        , id_role
        , id_str_role
        , name_role
        , place_type_role
        , url_role
    };
    explicit GeoSearch(QObject *parent = 0);
    ~GeoSearch();

public slots:
    void reload();

signals:
    void latitudeChanged(double latitude);
    void longitudeChanged(double longitude);
    void queryChanged(const QString &query);
    void ipChanged(const QString &ip);
    void granularityChanged(const QString &granularity);
    void accuracyChanged(const QString &accuracy);
    void max_resultsChanged(int max_results);
    void contained_withinChanged(const QString &contained_within);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/geo/search.json"); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;

    ADD_PROPERTY(double, latitude, double)
    ADD_PROPERTY(double, longitude, double)
    ADD_PROPERTY(const QString &, query, QString)
    ADD_PROPERTY(const QString &, ip, QString)
    ADD_PROPERTY(const QString &, granularity, QString)
    ADD_PROPERTY(const QString &, accuracy, QString)
    ADD_PROPERTY(int, max_results, int)
    ADD_PROPERTY(const QString &, contained_within, QString)
};

#endif // GEOSEARCH_H
