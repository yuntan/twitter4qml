#ifndef USERS_H
#define USERS_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

class Users : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Users)
public:
    explicit Users(QObject *parent = 0);
};

#endif // USERS_H
