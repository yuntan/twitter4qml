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

#ifndef TRENDSAVAILABLE_H
#define TRENDSAVAILABLE_H

#include "abstracttwittermodel.h"

class TWITTER4QML_EXPORT TrendsAvailable : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(TrendsAvailable)
public:
    enum Roles {
        country_role = Qt::UserRole + 1
        , country_code_role
        , name_role
        , parentid_role
        , place_type_role
        , url_role
        , woeid_role
    };
    explicit TrendsAvailable(QObject *parent = 0);

protected:
    virtual AuthorizeBy authenticationMethod() const { return AuthorizeByHeader; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("https://api.twitter.com/1.1/trends/available.json"); }
    void parseDone(const QVariant &result);
};

#endif // TRENDSAVAILABLE_H
