#ifndef DESTROYFAVIRITE_H
#define DESTROYFAVIRITE_H

#include "abstractfavoriteaction.h"

class DestroyFavorite : public AbstractFavoriteAction
{
    Q_OBJECT
    Q_DISABLE_COPY(DestroyFavorite)
public:
    explicit DestroyFavorite(QObject *parent = 0);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/favorites/destroy/%1.json").arg(id())); }
};

#endif // DESTROYFAVIRITE_H
