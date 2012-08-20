#ifndef USERSTREAM_H
#define USERSTREAM_H

#include "../statuses/abstractstatusesmodel.h"

class UserStream : public AbstractStatusesModel
{
    Q_OBJECT
    Q_PROPERTY(QString delimited READ delimited WRITE setDelimited NOTIFY delimitedChanged)
    Q_PROPERTY(QString replies READ replies WRITE setReplies NOTIFY repliesChanged)
    Q_PROPERTY(QStringList friends READ friends NOTIFY friendsChanged DESIGNABLE false)
    Q_DISABLE_COPY(UserStream)
public:
    explicit UserStream(QObject *parent = 0);
    ~UserStream();
    
    const QString &delimited() const;
    const QString &replies() const;
    const QStringList &friends() const;

public slots:
    void setDelimited(const QString &delimited);
    void setReplies(const QString &replies);

signals:
    void delimitedChanged(const QString &delimited);
    void repliesChanged(const QString &replies);
    void friendsChanged(const QStringList &friends);

    void followedBy(const QVariantMap &status);
    void favorited(const QVariantMap &status);
    void unfavorited(const QVariantMap &status);

protected:
    bool isStreaming() const { return true; }
    QUrl api() const { return QUrl("https://userstream.twitter.com/2/user.json"); }
    QString httpMethod() const { return "POST"; }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // USERSTREAM_H
