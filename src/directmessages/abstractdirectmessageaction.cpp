#include "abstractdirectmessageaction.h"

class AbstractDirectMessageAction::Private
{
public:
    Private();

    QString userId;
    QString screenName;
    QString text;
    QString id;
    bool includeEntities;
};

AbstractDirectMessageAction::Private::Private()
    : includeEntities(true)
{
}

AbstractDirectMessageAction::AbstractDirectMessageAction(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
}

AbstractDirectMessageAction::~AbstractDirectMessageAction()
{
    delete d;
}

const QString &AbstractDirectMessageAction::userId() const
{
    return d->userId;
}

void AbstractDirectMessageAction::setUserId(const QString &userId)
{
    if (d->userId == userId) return;
    d->userId = userId;
    emit userIdChanged(userId);
}

const QString &AbstractDirectMessageAction::screenName() const
{
    return d->screenName;
}

void AbstractDirectMessageAction::setScreenName(const QString &screenName)
{
    if (d->screenName == screenName) return;
    d->screenName = screenName;
    emit screenNameChanged(screenName);
}

const QString &AbstractDirectMessageAction::text() const
{
    return d->text;
}

void AbstractDirectMessageAction::setText(const QString &text)
{
    if (d->text == text) return;
    d->text = text;
    emit textChanged(text);
}

const QString &AbstractDirectMessageAction::id() const
{
    return d->id;
}

void AbstractDirectMessageAction::setId(const QString &id)
{
    if (d->id == id) return;
    d->id = id;
    emit idChanged(id);
}

bool AbstractDirectMessageAction::includeEntities() const
{
    return d->includeEntities;
}

void AbstractDirectMessageAction::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}
