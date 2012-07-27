#ifndef FAVORITE_H
#define FAVORITE_H

#include <QObject>

class Favorite : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(QString status_id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool favorited READ favorited WRITE setFavorited NOTIFY favoritedChanged)
public:
    explicit Favorite(QObject *parent = 0);
    
    bool loading() const;
    const QString &id() const;
    void setId(const QString &id);
    bool favorited() const;
    void setFavorited(bool favorited);

signals:
    void loadingChanged(bool loading);
    void idChanged(const QString &id);
    void favoritedChanged(bool favorited);
private:
    class Private;
    Private *d;
};

#endif // FAVORITE_H
