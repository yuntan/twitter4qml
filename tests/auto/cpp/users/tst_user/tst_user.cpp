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

#include <user.h>

class UserTest : public AbstractTwitter4QMLTest
{
    Q_OBJECT

private Q_SLOTS:
    void id_str();
    void id_str_data();
    void screen_name();
    void screen_name_data();
    void follow();
    void follow_data();
    void unfollow();
    void unfollow_data();

private:
    void data();
};

void UserTest::data()
{
    QTest::addColumn<QString>("id_str");
    QTest::addColumn<QString>("screen_name");

    QTest::newRow("Tasuku Suzuki") << "119039167" << "task_jp";
    QTest::newRow("Kenya 888") << "15394706" << "kenya888";
}

void UserTest::id_str()
{
    QFETCH(QString, id_str);
    QFETCH(QString, screen_name);

    User user;
    user.id_str(id_str);
    QCOMPARE(user.id_str(), id_str);

    QVERIFY2(wait(&user), "User::load");

    QCOMPARE(user.id_str(), id_str);
    QCOMPARE(user.screen_name(), screen_name);
}

void UserTest::id_str_data()
{
    data();
}

void UserTest::screen_name()
{
    QFETCH(QString, id_str);
    QFETCH(QString, screen_name);

    User user;
    user.screen_name(screen_name);
    QCOMPARE(user.screen_name(), screen_name);

    QVERIFY2(wait(&user), "User::load");

    QCOMPARE(user.id_str(), id_str);
    QCOMPARE(user.screen_name(), screen_name);
}

void UserTest::screen_name_data()
{
    data();
}

void UserTest::follow()
{
    QFETCH(QString, screen_name);

    User user;
    user.screen_name(screen_name);
    QVERIFY2(wait(&user), "User::load");

    user.follow();
    QVERIFY2(wait(&user), "User::follow");

    QCOMPARE(user.following(), true);
}

void UserTest::follow_data()
{
    data();
}

void UserTest::unfollow()
{
    QFETCH(QString, screen_name);

    User user;
    user.screen_name(screen_name);
    QVERIFY2(wait(&user), "User::load");

    user.unfollow();
    QVERIFY2(wait(&user), "User::unfollow");

    QCOMPARE(user.following(), false);
}

void UserTest::unfollow_data()
{
    data();
}

QTEST_MAIN(UserTest)

#include "tst_user.moc"
