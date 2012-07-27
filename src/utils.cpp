#include "utils.h"
#include "twitter4qml.h"
#include <QtCore/QMap>
#include <QtCore/QRegExp>

QString escapeHtml(const QString &text)
{
    static QMap<QString, QString> table;
    if (table.isEmpty()) {
        table.insert("&quot;", "\"");
        table.insert("&apos;", "'");
        table.insert("&lsquo;", QString::fromUtf8("‘"));
        table.insert("&rsquo;", QString::fromUtf8("’"));
        table.insert("&ldquo;", QString::fromUtf8("“"));
        table.insert("&rdquo;", QString::fromUtf8("”"));
        table.insert("&yen;", QString::fromUtf8("¥"));
        table.insert("&gt;", ">");
        table.insert("&lt;", "<");
        table.insert("&mdash;", QString::fromUtf8("—"));
        table.insert("\r\n", "\n");
        table.insert("\r", "\n");
    }

    QString ret = text;
    foreach (const QString &from, table.keys()) {
        ret.replace(from, table[from]);
    }
    {
        QRegExp regexp("&#x([0-9a-f]+);");
        while (regexp.indexIn(ret) != -1) {
            ret.replace(regexp.cap(0), QChar(regexp.cap(1).toInt(0, 16)));
        }
    }
    {
        QRegExp regexp("&#([0-9]+);");
        while (regexp.indexIn(ret) != -1) {
            ret.replace(regexp.cap(0), QChar(regexp.cap(1).toInt()));
        }
    }

    ret.replace("&amp;", "&");

//    if (text != ret) {
//        DEBUG() << text;
//        DEBUG() << ret;
//    }
    return ret;
}
