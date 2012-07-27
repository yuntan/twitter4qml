#include "tos.h"

class Tos::Private
{
public:
    QString tos;
};

Tos::Tos(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

Tos::~Tos()
{
    delete d;
}

const QString &Tos::tos() const
{
    return d->tos;
}

void Tos::setTos(const QString &tos)
{
    if (d->tos == tos) return;
    d->tos = tos;
    emit tosChanged(tos);
}
