#ifndef TWITTER4QML_H
#define TWITTER4QML_H

#include "twitter4qml_global.h"

#include <QtCore/QObject>

class QNetworkAccessManager;

class TWITTER4QML_EXPORT Twitter4QML : public QObject
{
    Q_OBJECT
public:
    explicit Twitter4QML(QObject *parent = 0);

    QNetworkAccessManager *networkAccessManager() const;

public slots:
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);

signals:
    void networkAccessManagerChanged(QNetworkAccessManager *networkAccessManager);

private:
    Q_DISABLE_COPY(Twitter4QML)
};

#endif // TWITTER4QML_H
