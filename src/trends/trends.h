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

#ifndef TRENDS_H
#define TRENDS_H

#include "../tools/abstracttwittermodel.h"

class Trends : public AbstractTwitterModel
{
    Q_OBJECT
    Q_PROPERTY(int woeid READ woeid WRITE setWoeid NOTIFY woeidChanged DESIGNABLE false)
    Q_PROPERTY(bool exclude READ exclude WRITE setExclude NOTIFY excludeChanged)
    Q_DISABLE_COPY(Trends)
public:
    enum Roles {
        QueryRole = Qt::UserRole + 1
        , NameRole
        , PromotedContentRole
        , EventsRole
        , UrlRole
    };
    explicit Trends(QObject *parent = 0);
    ~Trends();

    int woeid() const;
    void setWoeid(int woeid);
    bool exclude() const;
    void setExclude(bool exclude);

public slots:
    void reload();

signals:
    void woeidChanged(int woeid);
    void excludeChanged(bool exclude);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/trends/%1.json").arg(woeid())); }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // TRENDS_H
