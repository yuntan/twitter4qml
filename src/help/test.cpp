#include "test.h"
#include "twitter4qml_global.h"

class Test::Private
{
public:
    Private();
    bool ok;
};

Test::Private::Private()
    : ok(false)
{

}

Test::Test(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

Test::~Test()
{
    delete d;
}

void Test::setData(const QVariant &data)
{
    switch (data.type()) {
    case QVariant::Map:
    {
        QVariantMap map = data.toMap();
        if (map.contains("error")) {
            if (d->ok) {
                d->ok = false;
                emit isOkChanged(false);
            }
            DEBUG() << map.value("error");
        }
        break;
    }
    case QVariant::String:
        if (data.toString() == "ok") {
            if (!d->ok) {
                d->ok = true;
                emit isOkChanged(true);
            }
        } else {
            DEBUG() << data.toString();
        }
        break;
    default:
        DEBUG() << data;
        break;
    }
    AbstractTwitterAction::setData(data);
}

bool Test::isOk() const
{
    return d->ok;
}
