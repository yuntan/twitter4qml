#include "privacy.h"

class Privacy::Private
{
public:
    QString privacy;
};

Privacy::Privacy(QObject *parent)
    : AbstractTwitterAction(parent)
    , d(new Private)
{
    QMetaObject::invokeMethod(this, "exec", Qt::QueuedConnection);
}

Privacy::~Privacy()
{
    delete d;
}

const QString &Privacy::privacy() const
{
    return d->privacy;
}

void Privacy::setPrivacy(const QString &privacy)
{
    if (d->privacy == privacy) return;
    d->privacy = privacy;
    emit privacyChanged(privacy);
}
