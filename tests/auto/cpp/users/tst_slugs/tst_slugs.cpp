/* Copyright (c) 2012-2013 Twitter4QML Project.
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

#include "abstracttwitter4qmltest.h"

#include <users/slugs.h>

class SlugsTest : public AbstractTwitter4QMLTest
{
    Q_OBJECT

private Q_SLOTS:
    void lang();
    void lang_data();
};

void SlugsTest::lang()
{
    QFETCH(QString, data);

    Slugs slugs;
    QCOMPARE(slugs.lang(), QString());

    slugs.lang(data);
    QCOMPARE(slugs.lang(), data);

    QVERIFY2(reload(&slugs), "Slugs::reload()");

    QVERIFY2(slugs.rowCount() > 0, "contains data");
//    for (int i = 0; i < 2; i++) {
//        qDebug() << data << slugs.get(i).value("name").toString();
//    }
}

void SlugsTest::lang_data()
{
    QTest::addColumn<QString>("data");

    QTest::newRow("English") << "en";
    QTest::newRow("Spanish") << "es";
    QTest::newRow("Japanese") << "ja";
}

QTEST_MAIN(SlugsTest)

#include "tst_slugs.moc"
