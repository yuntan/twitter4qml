#ifndef LIST_H
#define LIST_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "twitter4qml_global.h"

class List : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(QString created_at READ createdAt WRITE setCreatedAt NOTIFY createdAtChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool following READ following WRITE setFollowing NOTIFY followingChanged)
    Q_PROPERTY(QString full_name READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString id_str READ idStr WRITE setIdStr NOTIFY idStrChanged)
    Q_PROPERTY(int member_count READ memberCount WRITE setMemberCount NOTIFY memberCountChanged)
    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString slug READ slug WRITE setSlug NOTIFY slugChanged)
    Q_PROPERTY(int subscriber_count READ subscriberCount WRITE setSubscriberCount NOTIFY subscriberCountChanged)
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)
    Q_PROPERTY(QVariantMap user READ user WRITE setUser NOTIFY userChanged)

    Q_DISABLE_COPY(List)
public:
    explicit List(QObject *parent = 0);

    static QVariantMap parse(const QVariantMap &status);

    bool loading() const;
    const QString &createdAt() const;
    const QString &description() const;
    bool following() const;
    const QString &fullName() const;
    const QString &idStr() const;
    int memberCount() const;
    const QString &mode() const;
    const QString &name() const;
    const QString &slug() const;
    int subscriberCount() const;
    const QString &uri() const;
    const QVariantMap &user() const;

    QVariantMap data() const;

    Q_INVOKABLE void createList(QVariantMap parameters);
    Q_INVOKABLE void updateList(QVariantMap parameters);
    Q_INVOKABLE void destroyList();
    Q_INVOKABLE void subscribe();
    Q_INVOKABLE void unsubscribe();

    Q_INVOKABLE void debug() const;

public slots:
    void setCreatedAt(const QString &createdAt);
    void setDescription(const QString &description);
    void setFollowing(bool following);
    void setFullName(const QString &fullName);
    void setIdStr(const QString &idStr);
    void setMemberCount(int memberCount);
    void setMode(const QString &mode);
    void setName(const QString &name);
    void setSlug(const QString &slug);
    void setSubscriberCount(int subscriberCount);
    void setUri(const QString &uri);
    void setUser(const QVariantMap &user);

signals:
    void loadingChanged(bool loading);
    void createdAtChanged(const QString &createdAt);
    void descriptionChanged(const QString &description);
    void followingChanged(bool following);
    void fullNameChanged(const QString &fullName);
    void idStrChanged(const QString &idStr);
    void memberCountChanged(int memberCount);
    void modeChanged(const QString &mode);
    void nameChanged(const QString &name);
    void slugChanged(const QString &slug);
    void subscriberCountChanged(int subscriberCount);
    void uriChanged(const QString &uri);
    void userChanged(const QVariantMap &user);
    void dataChanged();

private:
    class Private;
    Private *d;
};

#endif // LIST_H
