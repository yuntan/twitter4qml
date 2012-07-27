#include "hmac_sha1.h"
#include <QCryptographicHash>

static const int BLOCK_SIZE = 64;

QByteArray hmac_sha1(const QByteArray& in_key, const QByteArray& text)
{
    QByteArray key(in_key);
    if (key.length() > BLOCK_SIZE) {
        key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    }
    if (key.length() < BLOCK_SIZE) {
        key += QByteArray(BLOCK_SIZE-key.length(), 0);
    }
    QByteArray o_key_pad(BLOCK_SIZE, char(0x5c));
    QByteArray i_key_pad(BLOCK_SIZE, char(0x36));
    for (int i=0; i<BLOCK_SIZE; ++i) {
        o_key_pad[i] = o_key_pad[i] ^ key.at(i);
        i_key_pad[i] = i_key_pad[i] ^ key.at(i);
    }
    QByteArray ret = QCryptographicHash::hash(i_key_pad + text, QCryptographicHash::Sha1);
    ret = QCryptographicHash::hash(o_key_pad + ret, QCryptographicHash::Sha1);
    return ret;
}
