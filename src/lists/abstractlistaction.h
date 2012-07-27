#ifndef ABSTRACTLISTACTION_H
#define ABSTRACTLISTACTION_H

#include "../tools/abstracttwitteraction.h"

class AbstractListAction : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractListAction)
public:
    explicit AbstractListAction(QObject *parent = 0);
    ~AbstractListAction();

    const QString &listId() const;
    void setListId(const QString &listId);
    const QString &description() const;
    void setDescription(const QString &description);
    const QString &mode() const;
    void setMode(const QString &mode);
    const QString &name() const;
    void setName(const QString &name);

signals:
    void listIdChanged(const QString &listId);
    void descriptionChanged(const QString &description);
    void modeChanged(const QString &mode);
    void nameChanged(const QString &name);

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTLISTACTION_H
