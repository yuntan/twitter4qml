#ifndef NEWDIRECTMESSAGE_H
#define NEWDIRECTMESSAGE_H

#include "abstractdirectmessageaction.h"
#include <QtCore/QVariantMap>

class NewDirectMessage : public AbstractDirectMessageAction
{
    Q_OBJECT
    Q_PROPERTY(QString user_id READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString screen_name READ screenName WRITE setScreenName NOTIFY screenNameChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_DISABLE_COPY(NewDirectMessage)
public:
    explicit NewDirectMessage(QObject *parent = 0);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void textChanged(const QString &text);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/direct_messages/new.json"); }
};

#endif // NEWDIRECTMESSAGE_H
