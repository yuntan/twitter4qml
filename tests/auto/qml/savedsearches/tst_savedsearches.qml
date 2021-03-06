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

import QtTest 1.0
import TwitterAPI 1.1

TestCase {
    id: root

    OAuth {
        consumer_key: 'K6eWjgzGz1qE4oOOBYkdMg'
        consumer_secret: 't4ku8EEo8Sw7ywZ26vAxuQuH7sH0CQYH4DvhizEX4'
        token: '798286350-Za9khIT9UFYdNKMwjuha1zyrbeiVInr2p8iLtetk'
        token_secret: 'xfGg5t21TmJQdxxOpD4KYaxjRUZgIf8KIV33Z9s'
        user_id: '798286350'
        screen_name: 'twit_ter4qml'
    }

    SavedSearchesListModel {
        id: model
    }

    function initTestCase() {
        tryCompare(model, 'loading', true)
        tryCompare(model, 'loading', false, 10000)

        for (var i = 0; i < model.size; i++) {
            model.savedSearchesDestroy({id: model.get(i).id} )
            tryCompare(model, 'loading', true)
        }
        tryCompare(model, 'loading', false, 10000)
        tryCompare(model.size, 0)
    }

    function init() {
        model.reset()
    }

    function test_create_and_destroy() {
        model.reload()

        model.savedSearchesCreate({query: '#twitter4qml'})
        tryCompare(model, 'loading', true)
        tryCompare(model, 'loading', false, 10000)
        tryCompare(model.size, 1)

        model.savedSearchesDestroy({id: model.get(0).id} )
        tryCompare(model, 'loading', true)
        tryCompare(model, 'loading', false, 10000)
        tryCompare(model.size, 0)
    }
}
