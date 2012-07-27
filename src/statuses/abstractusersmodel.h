#ifndef ABSTRACTUSERSMODEL_H
#define ABSTRACTUSERSMODEL_H

#include "../tools/abstracttwittermodel.h"

class AbstractUsersModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractUsersModel)
public:
    enum Roles {
        ContributorsEnabled = Qt::UserRole + 1
        , CreatedAtRole
        , DefaultProfileRole
        , DefaultProfileImageRole
        , DescriptionRole
        , FavouritesCountRole
        , FollowRequestSentRole
        , FollowersCountRole
        , FollowingRole
        , FriendsCountRole
        , GeoEnabledRole
        , IdRole
        , IdStrRole
        , IsTranslatorRole
        , LangRole
        , ListedCountRole
        , LocationRole
        , NameRole
        , NotificationsRole
        , ProfileBackgroundColorRole
        , ProfileBackgroundImageUrlRole
        , ProfileBackgroundImageUrlHttpsRole
        , ProfileBackgroundTileRole
        , ProfileImageUrlRole
        , ProfileImageUrlHttpsRole
        , ProfileLinkColorRole
        , ProfileSidebarBorderColorRole
        , ProfileSidebarFillColorRole
        , ProfileTextColorRole
        , ProfileUseBackgroundImageRole
        , ProtectedRole
        , ScreenNameRole
        , ShowAllInlineMediaRole
        , StatusRole
        , StatusCountRole
        , TimeZoneRole
        , UrlRole
        , UtcOffsetRole
        , VerifiedRole
    };
    explicit AbstractUsersModel(QObject *parent = 0);
    ~AbstractUsersModel();

    const QString &id() const;
    void setId(const QString &id);
    int count() const;
    void setCount(int count);
    int page() const;
    void setPage(int page);

signals:
    void idChanged(const QString &id);
    void countChanged(int count);
    void pageChanged(int page);

protected:
    DataManager::DataType dataType() const { return DataManager::UserData; }
    AuthorizeBy authenticationMethod() const;
    QString httpMethod() const;
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTUSERSMODEL_H
