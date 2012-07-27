#ifndef DESTROYSAVEDSEARCH_H
#define DESTROYSAVEDSEARCH_H

#include "../tools/abstracttwitteraction.h"

class DestroySavedSearch : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString _id READ id WRITE setId NOTIFY idChanged DESIGNABLE false)
    Q_DISABLE_COPY(DestroySavedSearch)
public:
    DestroySavedSearch(QObject *parent = 0);
    ~DestroySavedSearch();

    const QString &id() const;
    void setId(const QString &id);

signals:
    void idChanged(const QString &id);

protected:
    QUrl api() const { return QUrl(QString("http://api.twitter.com/1/saved_searches/destroy/%1.json").arg(id())); }

private:
    class Private;
    Private *d;
};

#endif // DESTROYSAVEDSEARCH_H
