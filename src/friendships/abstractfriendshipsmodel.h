#ifndef ABSTRACTFRIENDSHIPSMODEL_H
#define ABSTRACTFRIENDSHIPSMODEL_H

#include "../tools/abstracttwittermodel.h"

class AbstractFriendshipsModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractFriendshipsModel)
public:
    enum Roles {
        CreatedAtRole = Qt::UserRole + 1
        , EntitiesRole
        , IdRole
        , RecipientRole
        , RecipientIdRole
        , RecipientScreenNameRole
        , SenderRole
        , SenderIdRole
        , SenderScreenNameRole
        , TextRole
    };
    explicit AbstractFriendshipsModel(QObject *parent = 0);
    ~AbstractFriendshipsModel();

    const QString &sinceId() const;
    void setSinceId(const QString &sinceId);
    const QString &maxId() const;
    void setMaxId(const QString &maxId);
    int count() const;
    void setCount(int count);
    int page() const;
    void setPage(int page);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);

signals:
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void countChanged(int count);
    void pageChanged(int page);
    void includeEntitiesChanged(bool includeEntities);

protected:
    AuthorizeBy authenticationMethod() const;
    QString httpMethod() const;
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTFRIENDSHIPSMODEL_H
