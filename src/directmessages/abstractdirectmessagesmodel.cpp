#include "abstractdirectmessagesmodel.h"
#include "directmessage.h"

class AbstractDirectMessagesModel::Private
{
public:
    Private();

    QString sinceId;
    QString maxId;
    int count;
    int page;
    bool includeEntities;
};

AbstractDirectMessagesModel::Private::Private()
    : count(0)
    , page(0)
    , includeEntities(true)
{
}

AbstractDirectMessagesModel::AbstractDirectMessagesModel(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[CreatedAtRole] = "created_at";
    roles[EntitiesRole] = "entities";
    roles[IdRole] = "id";
    roles[IdStrRole] = "id_str";
    roles[RecipientRole] = "recipient";
    roles[RecipientIdRole] = "recipient_id";
    roles[RecipientScreenNameRole] = "recipient_screen_name";
    roles[SenderRole] = "sender";
    roles[SenderIdRole] = "sender_id";
    roles[SenderScreenNameRole] = "sender_screen_name";
    roles[TextRole] = "text";
    roles[PlainTextRole] = "plain_text";
    roles[RichTextRole] = "rich_text";
    setRoleNames(roles);
}

AbstractDirectMessagesModel::~AbstractDirectMessagesModel()
{
    delete d;
}

AbstractTwitterModel::AuthorizeBy AbstractDirectMessagesModel::authenticationMethod() const
{
    return AuthorizeByUrl;
}

QString AbstractDirectMessagesModel::httpMethod() const
{
    return "GET";
}

void AbstractDirectMessagesModel::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::List) {
        QVariantList array = result.toList();
        foreach (const QVariant &result, array) {
            if (result.type() == QVariant::Map) {
                addData(DirectMessage::parse(result.toMap()));
            }
        }
    }
}

const QString &AbstractDirectMessagesModel::sinceId() const

{
    return d->sinceId;
}

void AbstractDirectMessagesModel::setSinceId(const QString &sinceId)
{
    if (d->sinceId == sinceId) return;
    d->sinceId = sinceId;
    emit sinceIdChanged(sinceId);
}

const QString &AbstractDirectMessagesModel::maxId() const
{
    return d->maxId;
}

void AbstractDirectMessagesModel::setMaxId(const QString &maxId)
{
    if (d->maxId == maxId) return;
    d->maxId = maxId;
    emit maxIdChanged(maxId);
}

int AbstractDirectMessagesModel::count() const
{
    return d->count;
}

void AbstractDirectMessagesModel::setCount(int count)
{
    if (d->count == count) return;
    d->count = count;
    emit countChanged(count);
}

int AbstractDirectMessagesModel::page() const
{
    return d->page;
}

void AbstractDirectMessagesModel::setPage(int page)
{
    if (d->page == page) return;
    d->page = page;
    emit pageChanged(page);
}

bool AbstractDirectMessagesModel::includeEntities() const
{
    return d->includeEntities;
}

void AbstractDirectMessagesModel::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}
