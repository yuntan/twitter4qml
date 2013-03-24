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

#include <updatestatus.h>
#include <verifycredentials.h>

class UpdateStatusTest : public AbstractTwitter4QMLTest
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void status();
    void status_data();
    void in_reply_to_status_id();
    void geo();
    void geo_data();

private:
    VerifyCredentials verifyCredentials;
    QString lastTweetId;
};

void UpdateStatusTest::initTestCase()
{
    QVERIFY2(exec(&verifyCredentials), "VerifyCredentials::exec()");
}

void UpdateStatusTest::status()
{
    QFETCH(QString, data);

    UpdateStatus updateStatus;
    QCOMPARE(updateStatus.status(), QString());

    QString tweet = QString("%1 - %2").arg(data).arg(QDateTime::currentDateTime().toString());
    updateStatus.status(tweet);
    QCOMPARE(updateStatus.status(), tweet);

    QVERIFY2(exec(&updateStatus), "UpdateStatus::exec()");

    QVariantMap response = updateStatus.data().toMap();

    QCOMPARE(response.value("id").isValid(), true);
    lastTweetId = response.value("id").toString();
}

void UpdateStatusTest::status_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("Test") << "Test";
    QTest::newRow("Tweet") << "Tweet";
}

void UpdateStatusTest::in_reply_to_status_id()
{
    QVERIFY2(!lastTweetId.isEmpty(), "in_reply_to_status_id is empty");

    UpdateStatus updateStatus;

    updateStatus.status(QString("@%1 %2").arg(verifyCredentials.screen_name()).arg(QDateTime::currentDateTime().toString()));
    updateStatus.in_reply_to_status_id(lastTweetId);

    QVERIFY2(exec(&updateStatus), "UpdateStatus::exec()");

    QVariantMap response = updateStatus.data().toMap();

    QCOMPARE(response.value("id").isValid(), true);
    QCOMPARE(response.value("in_reply_to_status_id").toString(), lastTweetId);
}

void UpdateStatusTest::geo()
{
    QFETCH(QString, name);
    QFETCH(double, latitude);
    QFETCH(double, longitude);
    UpdateStatus updateStatus;

    updateStatus.status(QString("%1 %2").arg(name).arg(QDateTime::currentDateTime().toString()));
    updateStatus.latitude(latitude);
    updateStatus.longitude(longitude);

    QVERIFY2(exec(&updateStatus), "UpdateStatus::exec()");

    QVariantMap response = updateStatus.data().toMap();
    QCOMPARE(response.value("id").isValid(), true);
    QCOMPARE(response.value("geo").isValid(), verifyCredentials.geo_enabled());
}

void UpdateStatusTest::geo_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<double>("latitude");
    QTest::addColumn<double>("longitude");
    QTest::newRow("Example") << QString("Example") << 37.7821120598956 << -122.400612831116;
    QTest::newRow("Mt. Fuji") << QString("Mt. Fuji") << 35.362892 << 138.730467;
    QTest::newRow("Great Pyramid of Giza") << QString("Great Pyramid of Giza") << 29.979025 << 31.134194;
}

QTEST_MAIN(UpdateStatusTest)

#include "tst_updatestatus.moc"
