#ifndef ABSTRACTDIRECTMESSAGEACTION_H
#define ABSTRACTDIRECTMESSAGEACTION_H

#include "../tools/abstracttwitteraction.h"

class AbstractDirectMessageAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractDirectMessageAction)
public:
    explicit AbstractDirectMessageAction(QObject *parent = 0);
    ~AbstractDirectMessageAction();

    const QString &userId() const;
    void setUserId(const QString &userId);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    const QString &text() const;
    void setText(const QString &text);
    const QString &id() const;
    void setId(const QString &id);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void textChanged(const QString &text);
    void idChanged(const QString &id);
    void includeEntitiesChanged(bool includeEntities);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "POST"; }

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTDIRECTMESSAGEACTION_H
