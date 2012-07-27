#ifndef STATUSES_H
#define STATUSES_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

class Statuses : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Statuses)

public:
    explicit Statuses(QObject *parent = 0);
    
};

#endif // STATUSES_H
