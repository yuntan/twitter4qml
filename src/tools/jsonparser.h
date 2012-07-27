#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

#include "twitter4qml.h"

class JSONParser : public QObject
{
    Q_OBJECT
public:
    explicit JSONParser(QObject *parent = 0);
    ~JSONParser();

public slots:
    void parse(const QByteArray &data);

signals:
    void parsed(const QVariant &result);

private:
    class Private;
    Private *d;
};

#endif // JSONPARSER_H
