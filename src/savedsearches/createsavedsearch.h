#ifndef CREATESAVEDSEARCH_H
#define CREATESAVEDSEARCH_H

#include "../tools/abstracttwitteraction.h"

class CreateSavedSearch : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString query READ query WRITE setQuery NOTIFY queryChanged)
    Q_DISABLE_COPY(CreateSavedSearch)
public:
    CreateSavedSearch(QObject *parent = 0);
    ~CreateSavedSearch();

    const QString &query() const;
    void setQuery(const QString &query);

signals:
    void queryChanged(const QString &query);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/saved_searches/create.json"); }

private:
    class Private;
    Private *d;
};

#endif // CREATESAVEDSEARCH_H
