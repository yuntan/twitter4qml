#ifndef SHOWDIRECTMESSAGE_H
#define SHOWDIRECTMESSAGE_H

#include "abstractdirectmessageaction.h"

class ShowDirectMessage : public AbstractDirectMessageAction
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_DISABLE_COPY(ShowDirectMessage)
public:
    explicit ShowDirectMessage(QObject *parent = 0);

public slots:
    void exec();

signals:
    void idChanged(const QString &id);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/direct_messages/show/%1.json").arg(id())); }
    QString httpMethod() const { return "GET"; }
};

#endif // SHOWDIRECTMESSAGE_H
