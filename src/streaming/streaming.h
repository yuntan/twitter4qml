#ifndef STREAMING_H
#define STREAMING_H

#include <QtCore/QObject>

class Streaming : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Streaming)
public:
    explicit Streaming(QObject *parent = 0);
};

#endif // STREAMING_H
