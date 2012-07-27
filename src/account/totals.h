#ifndef TOTALS_H
#define TOTALS_H

#include "../tools/abstracttwitteraction.h"

class Totals : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(Totals)
    Q_PROPERTY(int friends READ friends WRITE setFriends NOTIFY friendsChanged DESIGNABLE false USER true)
    Q_PROPERTY(int updates READ updates WRITE setUpdates NOTIFY updatesChanged DESIGNABLE false USER true)
    Q_PROPERTY(int followers READ followers WRITE setFollowers NOTIFY followersChanged DESIGNABLE false USER true)
    Q_PROPERTY(int favorites READ favorites WRITE setFavorites NOTIFY favoritesChanged DESIGNABLE false USER true)
public:
    explicit Totals(QObject *parent = 0);
    ~Totals();

    int friends() const;
    void setFriends(int friends);
    int updates() const;
    void setUpdates(int updates);
    int followers() const;
    void setFollowers(int followers);
    int favorites() const;
    void setFavorites(int favorites);

signals:
    void friendsChanged(int friends);
    void updatesChanged(int updates);
    void followersChanged(int followers);
    void favoritesChanged(int favorites);

protected:
    QUrl api() const { return QUrl("https://api.twitter.com/1/account/totals.json"); }
    QString httpMethod() const { return "GET"; }

private:
    class Private;
    Private *d;
};

#endif // TOTALS_H
