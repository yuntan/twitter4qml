#ifndef SHOWFRIENDSHIP_H
#define SHOWFRIENDSHIP_H

#include "../tools/abstracttwitteraction.h"

class ShowFriendships : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString source_id READ sourceId WRITE setSourceId NOTIFY sourceIdChanged)
    Q_PROPERTY(QString source_screen_name READ sourceScreenName WRITE setSourceScreenName NOTIFY sourceScreenNameChanged)
    Q_PROPERTY(QString target_id READ targetId WRITE setTargetId NOTIFY targetIdChanged)
    Q_PROPERTY(QString target_screen_name READ targetScreenName WRITE setTargetScreenName NOTIFY targetScreenNameChanged)
    Q_PROPERTY(QVariantMap relationship READ relationship WRITE setRelationship NOTIFY relationshipChanged DESIGNABLE false USER true)
public:
    explicit ShowFriendships(QObject *parent = 0);

    const QString &sourceId() const;
    void setSourceId(const QString &sourceId);
    const QString &sourceScreenName() const;
    void setSourceScreenName(const QString &sourceScreenName);
    const QString &targetId() const;
    void setTargetId(const QString &targetId);
    const QString &targetScreenName() const;
    void setTargetScreenName(const QString &targetScreenName);
    const QVariantMap &relationship() const;
    void setRelationship(const QVariantMap &relationship);

public slots:
    void exec();

signals:
    void sourceIdChanged(const QString &sourceId);
    void sourceScreenNameChanged(const QString &sourceScreenName);
    void targetIdChanged(const QString &targetId);
    void targetScreenNameChanged(const QString &targetScreenName);
    void relationshipChanged(const QVariantMap &relationship);
protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/friendships/show.json"); }
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }

private:
    class Private;
    Private *d;
};

#endif // SHOWFRIENDSHIP_H
