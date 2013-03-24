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

#ifndef ACTIVITYSUMMARY_H
#define ACTIVITYSUMMARY_H

#include "abstracttwitteraction.h"

class TWITTER4QML_EXPORT ActivitySummary : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE id NOTIFY idChanged DESIGNABLE false)
    Q_PROPERTY(QVariantList favoriters READ favoriters WRITE setFavoriters NOTIFY favoritersChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString favoriters_count READ favoritersCount WRITE setFavoritersCount NOTIFY favoritersCountChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantList repliers READ repliers WRITE setRepliers NOTIFY repliersChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString repliers_count READ repliersCount WRITE setRepliersCount NOTIFY repliersCountChanged DESIGNABLE false USER true)
    Q_PROPERTY(QString retweeters_count READ retweetersCount WRITE setRetweetersCount NOTIFY retweetersCountChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantList retweeters READ retweeters WRITE setRetweeters NOTIFY retweetersChanged DESIGNABLE false USER true)
public:
    explicit ActivitySummary(QObject *parent = 0);
    ~ActivitySummary();

    const QString &id() const;
    const QVariantList &favoriters() const;
    const QString &favoritersCount() const;
    const QVariantList &repliers() const;
    const QString &repliersCount() const;
    const QString &retweetersCount() const;
    const QVariantList &retweeters() const;

public slots:
    void exec();
    void id(const QString &id);
    void setFavoriters(const QVariantList &favoriters);
    void setFavoritersCount(const QString &favoritersCount);
    void setRepliers(const QVariantList &repliers);
    void setRepliersCount(const QString &repliersCount);
    void setRetweetersCount(const QString &retweetersCount);
    void setRetweeters(const QVariantList &retweeters);

signals:
//    void loadingChanged(bool loading);
    void idChanged(const QString &id);
    void favoritersChanged(const QVariantList &favoriters);
    void favoritersCountChanged(const QString &favoritersCount);
    void repliersChanged(const QVariantList &repliers);
    void repliersCountChanged(const QString &repliersCount);
    void retweetersCountChanged(const QString &retweetersCount);
    void retweetersChanged(const QVariantList &retweeters);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/i/statuses/%1/activity/summary.json").arg(id())); }
    QString httpMethod() const { return "GET"; }

private:
    Q_DISABLE_COPY(ActivitySummary)
    class Private;
    Private *d;
};

#endif // ACTIVITYSUMMARY_H
