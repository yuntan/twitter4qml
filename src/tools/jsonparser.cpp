/* Copyright (c) 2012 Twitter4QML Project.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Twitter4QML nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL TWITTER4QML BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "jsonparser.h"
#include <QtCore/QThread>
#include <QtCore/QReadLocker>
#include <QtCore/QWriteLocker>

class JSONParser::Private : public QObject
{
    Q_OBJECT
public:
    Private(JSONParser *parent);

public slots:
    void parse(const QByteArray &data);
    void cancel();

private:
    JSONParser *q;
    QReadWriteLock lock;
    bool cancelling;

    const char *parseValue(const char *ch, QVariant *value, bool *ok = 0);
    const char *parseNull(const char *ch, QVariant *value, bool *ok = 0);
    const char *parseTrue(const char *ch, QVariant *value, bool *ok = 0);
    const char *parseFalse(const char *ch, QVariant *value, bool *ok = 0);
    const char *parseNumber(const char *ch, QVariant *value, bool *ok = 0);
    const char *parseString(const char *ch, QVariant *value, bool *ok = 0);
    const char *parseArray(const char *ch, QVariant *value, bool *ok = 0);
    const char *parseObject(const char *ch, QVariant *value, bool *ok = 0);
public:
    QThread *thread;
};

JSONParser::Private::Private(JSONParser *parent)
    : q(parent)
    , cancelling(false)
    , thread(new QThread(parent))
{
}

void JSONParser::Private::parse(const QByteArray &data)
{
    {
        QWriteLocker locker(&lock);
        cancelling = false;
    }
    const char *ch = data.constData();
    if (*ch != 0) {
        bool ok;
        QVariant value;
        ch = parseValue(ch, &value, &ok);
        QReadLocker locker(&lock);
        if (!cancelling) {
            if (ok) {
                QMetaObject::invokeMethod(q, "parsed", Qt::QueuedConnection, Q_ARG(QVariant, value));
            } else {
                QMetaObject::invokeMethod(q, "parsed", Qt::QueuedConnection, Q_ARG(QVariant, QVariant()));
            }
        }
    }
}

void JSONParser::Private::cancel() {
    QWriteLocker locker(&lock);
    cancelling = true;
}

const char *JSONParser::Private::parseValue(const char *ch, QVariant *value, bool *ok)
{
    if (ok) *ok = false;
    bool break2 = false;
    while (*ch != 0 && !break2) {
        QReadLocker locker(&lock);
        if (cancelling) return ch;
        switch (*ch) {
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            ch++;
            break;
        case '{':
            ch = parseObject(ch, value, ok);
            break2 = true;
            break;
        case '[':
            ch = parseArray(ch, value, ok);
            break2 = true;
            break;
        case '"':
            ch = parseString(ch, value, ok);
            break2 = true;
            break;
        case 't':
            ch = parseTrue(ch, value, ok);
            break2 = true;
            break;
        case 'f':
            ch = parseFalse(ch, value, ok);
            break2 = true;
            break;
        case 'n':
            ch = parseNull(ch, value, ok);
            break2 = true;
            break;
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            ch = parseNumber(ch, value, ok);
            break2 = true;
            break;
        default:
            DEBUG() << *ch;
            ch++;
            break2 = true;
            break;
        }
    }
    return ch;
}

const char *JSONParser::Private::parseNull(const char *ch, QVariant *value, bool *ok)
{
    if (ok) *ok = false;
    ch++;
    if (!*ch || *ch != 'u') return ch;
    ch++;
    if (!*ch || *ch != 'l') return ch;
    ch++;
    if (!*ch || *ch != 'l') return ch;
    ch++;
    value->clear();
    if (ok) *ok = true;
    return ch;
}

const char *JSONParser::Private::parseTrue(const char *ch, QVariant *value, bool *ok)
{
    if (ok) *ok = false;
    ch++;
    if (!*ch || *ch != 'r') return ch;
    ch++;
    if (!*ch || *ch != 'u') return ch;
    ch++;
    if (!*ch || *ch != 'e') return ch;
    ch++;
    value->setValue(true);
    if (ok) *ok = true;
    return ch;
}

const char *JSONParser::Private::parseFalse(const char *ch, QVariant *value, bool *ok)
{
    if (ok) *ok = false;
    ch++;
    if (!*ch || *ch != 'a') return ch;
    ch++;
    if (!*ch || *ch != 'l') return ch;
    ch++;
    if (!*ch || *ch != 's') return ch;
    ch++;
    if (!*ch || *ch != 'e') return ch;
    ch++;
    value->setValue(false);
    if (ok) *ok = true;
    return ch;
}

const char *JSONParser::Private::parseNumber(const char *ch, QVariant *value, bool *ok)
{
    if (ok) *ok = false;
    QString ret;
//    qDebug() << __LINE__ << *ch;
    bool break2 = false;
    bool containsPeriod = false;
    while (!break2) {
        switch (*ch) {
        case '.':
            containsPeriod = true;
        case '-':
        case '+':
        case 'e':
        case 'E':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            ret.append(*ch);
            ch++;
//            qDebug() << __LINE__ << *ch;
            break;
        default:
            break2 = true;
            break;
        }
    }
//    qDebug() << ret;
    if (containsPeriod) {
        value->setValue(ret.toFloat(ok));
    } else {
        value->setValue(ret.toInt(ok));
        if (!*ok)
            value->setValue(ret.toLongLong(ok));
    }
    return ch;
}

const char *JSONParser::Private::parseString(const char *ch, QVariant *value, bool *ok)
{
    if (ok) *ok = false;
    QByteArray utf8;
    QString ret;
    ch++;
    bool break2 = false;
    bool escaping = false;
    while (!break2) {
        switch (*ch) {
        case 0:
            return ch;
        case '\\':
            if (escaping) {
                ret.append(*ch);
            }
            escaping = !escaping;
            ch++;
            break;
        case '"':
            if (escaping) {
                escaping = false;
                ret.append(*ch);
            } else {
                break2 = true;
            }
            ch++;
            break;
        case 'u':
            if (escaping) {
                escaping = false;
                utf8 = QByteArray("");
            } else {
                ret.append(*ch);
            }
            ch++;
            break;
        case 'n':
            if (escaping) {
                escaping = false;
                ret.append('\n');
            } else {
                ret.append(*ch);
            }
            ch++;
            break;
        case 'r':
            if (escaping) {
                escaping = false;
                ret.append('\r');
            } else {
                ret.append(*ch);
            }
            ch++;
            break;
        default:
            if (!utf8.isNull()) {
                utf8.append(*ch);
                if (utf8.length() == 4) {
                    ret.append(utf8.toInt(0, 16));
                    utf8.clear();
                }
            } else {
                if (escaping) {
//                    ret.append('\\');
                    escaping = false;
                }
                ret.append(*ch);
            }
            ch++;
            break;
        }
    }
    value->setValue(ret);
    if (ok) *ok = true;
    return ch;
}

const char *JSONParser::Private::parseArray(const char *ch, QVariant *value, bool *ok)
{
    if (ok) *ok = false;
    ch++;
    QVariantList ret;
    bool break2 = false;
    while (!break2) {
        switch (*ch) {
        case 0:
            return ch;
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            ch++;
            break;
        case ']':
            ch++;
            break2 = true;
            break;
        case ',':
            ch++;
            break;
        default: {
            QVariant value;
            bool ok = false;
            ch = parseValue(ch, &value, &ok);
            if (!ok) return ch;
            ret.append(value);
            break;
        }
        }
    }
    value->setValue(ret);
    if (ok) *ok = true;
    return ch;
}

const char *JSONParser::Private::parseObject(const char *ch, QVariant *value, bool *ok)
{
    if (ok) *ok = false;
    ch++;
    QVariantMap ret;
    bool break2 = false;
    QString key;
    while (!break2) {
        switch (*ch) {
        case 0:
            return ch;
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            ch++;
            break;
        case ':':
            if (key.isNull()) return ch;
            ch++;
            break;
        case '}':
            ch++;
            break2 = true;
            break;
        case ',':
            ch++;
            break;
        default: {
            QVariant value;
            bool ok = false;
            if (key.isNull()) {
                ch = parseValue(ch, &value, &ok);
                if (!ok) return ch;
                if (value.type() != QVariant::String) return ch;
                key = value.toString();
            } else {
                ch = parseValue(ch, &value, &ok);
                if (!ok) return ch;
                ret.insert(key, value);
                key.clear();
            }
            break;
        }
        }
    }
    value->setValue(ret);
    if (ok) *ok = true;
    return ch;
}

JSONParser::JSONParser(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
    d->thread->start(QThread::LowPriority);
    d->moveToThread(d->thread);
}

JSONParser::~JSONParser()
{
    QThread* thread = d->thread;
    delete d;
    thread->quit();
    thread->wait();
    delete thread;
}

void JSONParser::parse(const QByteArray &data)
{
    QMetaObject::invokeMethod(d, "parse", Qt::QueuedConnection, Q_ARG(QByteArray, data));
}

void JSONParser::cancel()
{
    d->cancel();
}

#include "jsonparser.moc"
