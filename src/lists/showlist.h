#ifndef SHOWLIST_H
#define SHOWLIST_H

#include "abstractlistaction.h"

class ShowList : public AbstractListAction
{
    Q_OBJECT
    Q_PROPERTY(QString list_id READ listId WRITE setListId NOTIFY listIdChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_DISABLE_COPY(ShowList)
public:
    explicit ShowList(QObject *parent = 0);

public slots:
    void exec();

signals:
    void listIdChanged(const QString &listId);
    void descriptionChanged(const QString &description);
    void modeChanged(const QString &mode);
    void nameChanged(const QString &name);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/lists/show.json"); }
    QString httpMethod() const { return "GET"; }
};

#endif // SHOWLIST_H
