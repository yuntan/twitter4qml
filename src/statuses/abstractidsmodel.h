#ifndef ABSTRACTIDSMODEL_H
#define ABSTRACTIDSMODEL_H

#include "../tools/abstracttwittermodel.h"

class AbstractIdsModel : public AbstractTwitterModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractIdsModel)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1
        , IdStrRole
    };
    explicit AbstractIdsModel(QObject *parent = 0);
    ~AbstractIdsModel();

    const QString &id() const;
    void setId(const QString &id);
    int count() const;
    void setCount(int count);
    int page() const;
    void setPage(int page);
    bool stringifyIds() const;
    void setStringifyIds(bool stringifyIds);

    DataManager::DataType dataType() const { return DataManager::NoData; }

signals:
    void idChanged(const QString &id);
    void countChanged(int count);
    void pageChanged(int page);
    void stringifyIdsChanged(bool stringifyIds);

protected:
    AuthorizeBy authenticationMethod() const;
    QString httpMethod() const;
    void parseDone(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTIDSMODEL_H
