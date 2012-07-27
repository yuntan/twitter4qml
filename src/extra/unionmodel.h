#ifndef UNIONMODEL_H
#define UNIONMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QStringList>
#include <QtDeclarative/QDeclarativeListProperty>

class UnionModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(QDeclarativeListProperty<QObject> childObjects READ childObjects DESIGNABLE false)
    Q_PROPERTY(QStringList idList READ idList NOTIFY idListChanged DESIGNABLE false)
    Q_PROPERTY(int size READ size NOTIFY sizeChanged DESIGNABLE false)
    Q_CLASSINFO("DefaultProperty", "childObjects")
    Q_DISABLE_COPY(UnionModel)
public:
    explicit UnionModel(QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    
    virtual bool isLoading() const;
    QDeclarativeListProperty<QObject> childObjects();

    Q_INVOKABLE void addModel(QObject *model) const;
    Q_INVOKABLE QVariantMap get(int index) const;
    const QStringList &idList() const;
    Q_INVOKABLE int size() { return rowCount(); }
    Q_INVOKABLE int indexOf(const QString &id);

public slots:
    void reload();

signals:
    void loadingChanged(bool loading);
    void idListChanged(const QStringList &idList);
    void sizeChanged();

private:
    class Private;
    Private *d;
};

#endif // UNIONMODEL_H
