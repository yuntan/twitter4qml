#ifndef ABSTRACTSTATUSESMODEL_H
#define ABSTRACTSTATUSESMODEL_H

#include "../tools/abstracttwittermodel.h"

class AbstractStatusesModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractStatusesModel)
public:
    enum Roles {
        ContributorsRole = Qt::UserRole + 1
        , CoordinatesRole
        , CreatedAtRole
        , EntitiesRole
        , FavoritedRole
        , GeoRole
        , IdRole
        , IdStrRole
        , InReplyToScreenNameRole
        , InReplyToStatusIdRole
        , InReplyToUserIdRole
        , PlaceRole
        , PossiblySensitiveRole
        , RetweetCountRole
        , RetweetedRole
        , RetweetedStatusRole
        , SourceRole
        , TextRole
        , PlainTextRole
        , RichTextRole
        , TruncatedRole
        , UserRole
        , MediaRole
    };
    explicit AbstractStatusesModel(QObject *parent = 0);
    ~AbstractStatusesModel();

    const QString &userId() const;
    void setUserId(const QString &userId);
    const QString &screenName() const;
    void setScreenName(const QString &screenName);
    const QString &id() const;
    void setId(const QString &id);
    int count() const;
    void setCount(int count);
    const QString &sinceId() const;
    void setSinceId(const QString &sinceId);
    const QString &maxId() const;
    void setMaxId(const QString &maxId);
    int page() const;
    void setPage(int page);
    bool trimUser() const;
    void setTrimUser(bool trimUser);
    bool includeRts() const;
    void setIncludeRts(bool includeRts);
    bool excludeReplies() const;
    void setExcludeReplies(bool excludeReplies);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);
    bool contributorDetails() const;
    void setContributorDetails(bool contributorDetails);
    const QString &listId() const;
    void setListId(const QString &listId);
    int perPage() const;
    void setPerPage(int perPage);

    DataManager::DataType dataType() const { return DataManager::StatusData; }

signals:
    void userIdChanged(const QString &userId);
    void screenNameChanged(const QString &screenName);
    void idChanged(const QString &id);
    void countChanged(int count);
    void sinceIdChanged(const QString &sinceId);
    void maxIdChanged(const QString &maxId);
    void pageChanged(int page);
    void trimUserChanged(bool trimUser);
    void includeRtsChanged(bool includeRts);
    void excludeRepliesChanged(bool excludeReplies);
    void includeEntitiesChanged(bool includeEntities);
    void contributorDetailsChanged(bool contributorDetails);
    void listIdChanged(const QString &listId);
    void perPageChanged(int perPage);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTSTATUSESMODEL_H
