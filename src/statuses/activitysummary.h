#ifndef ACTIVITYSUMMARY_H
#define ACTIVITYSUMMARY_H

#include "../tools/abstracttwitteraction.h"

class ActivitySummary : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
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
    void setId(const QString &id);
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
