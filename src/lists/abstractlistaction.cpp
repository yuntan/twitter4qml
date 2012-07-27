#include "abstractlistaction.h"

class AbstractListAction::Private
{
public:
    QString listId;
    QString description;
    QString mode;
    QString name;
};

AbstractListAction::AbstractListAction(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

AbstractListAction::~AbstractListAction()
{
    delete d;
}

const QString &AbstractListAction::listId() const
{
    return d->listId;
}

void AbstractListAction::setListId(const QString &listId)
{
    if (d->listId == listId) return;
    d->listId = listId;
    emit listIdChanged(listId);
}

const QString &AbstractListAction::description() const
{
    return d->description;
}

void AbstractListAction::setDescription(const QString &description)
{
    if (d->description == description) return;
    d->description = description;
    emit descriptionChanged(description);
}

const QString &AbstractListAction::mode() const
{
    return d->mode;
}

void AbstractListAction::setMode(const QString &mode)
{
    if (d->mode == mode) return;
    d->mode = mode;
    emit modeChanged(mode);
}

const QString &AbstractListAction::name() const
{
    return d->name;
}

void AbstractListAction::setName(const QString &name)
{
    if (d->name == name) return;
    d->name = name;
    emit nameChanged(name);
}

