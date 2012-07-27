#ifndef CREATEFAVORITE_H
#define CREATEFAVORITE_H

#include "abstractfavoriteaction.h"

class CreateFavorite : public AbstractFavoriteAction
{
    Q_OBJECT
    Q_DISABLE_COPY(CreateFavorite)
public:
    explicit CreateFavorite(QObject *parent = 0);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/favorites/create/%1.json").arg(id())); }
};

#endif // CREATEFAVORITE_H
