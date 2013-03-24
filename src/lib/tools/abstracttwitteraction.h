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

#ifndef ABSTRACTTWITTERACTION_H
#define ABSTRACTTWITTERACTION_H

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVariantMap>

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

class TWITTER4QML_EXPORT AbstractTwitterAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(QVariant data READ data NOTIFY dataChanged DESIGNABLE false)
    Q_DISABLE_COPY(AbstractTwitterAction)
public:
    enum AuthorizeBy {
        AuthorizeByHeader,
        AuthorizeByBody,
        AuthorizeByUrl
    };
    explicit AbstractTwitterAction(QObject *parent = 0);

    bool isLoading() const;
    const QVariant &data() const;

public slots:
    virtual void exec();

signals:
    void loadingChanged(bool isLoading);
    void dataChanged(const QVariant &data);

protected slots:
    void setParameters(const QVariantMap &parameters);

protected:
    void setLoading(bool isLoading);
    virtual void setData(const QVariant &data);

    virtual QUrl api() const = 0;
    virtual bool isMultiPart() const { return false; }
    virtual AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    virtual QString httpMethod() const { return "POST"; }

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTTWITTERACTION_H
