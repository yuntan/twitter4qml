#ifndef HMAC_SHA1_H
#define HMAC_SHA1_H

#include <QByteArray>

QByteArray hmac_sha1(const QByteArray& key, const QByteArray& text);

#endif // HMAC_SHA1_H
