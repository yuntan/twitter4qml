#ifndef CREATELIST_H
#define CREATELIST_H

#include "abstractlistaction.h"

class CreateList : public AbstractListAction
{
    Q_OBJECT
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_DISABLE_COPY(CreateList)
public:
    explicit CreateList(QObject *parent = 0);

signals:
    void descriptionChanged(const QString &description);
    void modeChanged(const QString &mode);
    void nameChanged(const QString &name);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/create.json"); }
};

#endif // CREATELIST_H
