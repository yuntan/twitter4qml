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

#include <oauth/oauth.h>
#include <tools/oauthmanager.h>

#include <tools/abstracttwitteraction.h>
#include <tools/abstracttwittermodel.h>

AbstractTwitter4QMLTest::AbstractTwitter4QMLTest(QObject *parent)
    : QObject(parent)
{
    OAuth oauth;
    oauth.setConsumerKey(QLatin1String("K6eWjgzGz1qE4oOOBYkdMg"));
    oauth.setConsumerSecret(QLatin1String("t4ku8EEo8Sw7ywZ26vAxuQuH7sH0CQYH4DvhizEX4"));
    oauth.setToken(QLatin1String("798286350-Za9khIT9UFYdNKMwjuha1zyrbeiVInr2p8iLtetk"));
    oauth.setTokenSecret(QLatin1String("xfGg5t21TmJQdxxOpD4KYaxjRUZgIf8KIV33Z9s"));
    OAuthManager::instance().setAuthorized(true);
}

bool AbstractTwitter4QMLTest::exec(AbstractTwitterAction *action)
{
    action->exec();

    QTime timer;
    timer.start();
    while (action->isLoading()) {
        if (timer.elapsed() > 1000 * 30) break;
        QTest::qWait(100);
    }
    return !action->isLoading();
}

bool AbstractTwitter4QMLTest::reload(AbstractTwitterModel *model)
{
    model->reload();

    QTime timer;
    timer.start();
    while (model->isLoading()) {
        if (timer.elapsed() > 1000 * 30) break;
        QTest::qWait(100);
    }
    return !model->isLoading();
}
