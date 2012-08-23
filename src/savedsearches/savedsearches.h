#ifndef SAVEDSEARCHES_H
#define SAVEDSEARCHES_H

#include "../tools/abstracttwittermodel.h"

class SavedSearches : public AbstractTwitterModel
{
    Q_OBJECT
public:
    enum Roles {
        CreatedAtRole = Qt::UserRole + 1
        , IdRole
        , IdStrRole
        , NameRole
        , PositionRole
        , QueryRole
    };
    explicit SavedSearches(QObject *parent = 0);

    Q_INVOKABLE void createSavedSearch(QVariantMap parameters);
    Q_INVOKABLE void destroySavedSearch(QVariantMap parameters);

    bool isLoading() const;
    DataManager::DataType dataType() const { return DataManager::SavedSearchData; }

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/saved_searches.json"); }
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    void parseDone(const QVariant &result);

    void dataAdded(const QString &key, const QVariantMap &value);
    void dataAboutToBeRemoved(const QString &key, const QVariantMap &value);

private:
    Q_DISABLE_COPY(SavedSearches)
    class Private;
    Private *d;
};

#endif // SAVEDSEARCHES_H
