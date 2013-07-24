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

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/qqml.h>
#else
#include <QtDeclarative/QDeclarativeExtensionPlugin>
#include <QtDeclarative/qdeclarative.h>
#endif

// Timelines
#include <mentionstimeline.h>
#include <hometimeline.h>
#include <usertimeline.h>
#include <retweetsofme.h>

// Tweets
#include <retweets.h>
#include <status.h>

// Search
#include <search.h>

// Streaming
#include <userstream.h>
#include <filterstream.h>
#include <samplestream.h>

// Direct Messages
#include <directmessages.h>
#include <directmessagessent.h>
#include <directmessage.h>

// Friends & Followers
#include <noretweetsids.h>
#include <followersids.h>
#include <friendsids.h>
#include <incoming.h>
#include <outgoing.h>
#include <followers.h>
#include <friends.h>
#include <showfriendships.h>

// Users
#include <settings.h>
#include <verifycredentials.h>
#include <updatesettings.h>
#include <updateprofile.h>
#include <blockslist.h>
#include <blocksids.h>
#include <lookupusers.h>
#include <user.h>
#include <searchusers.h>

// Suggested Users
#include <slugs.h>
#include <suggestions.h>

// Favorites
#include <favoriteslist.h>

// Lists
#include <lists.h>
#include <listsstatuses.h>
#include <listsmemberships.h>
#include <listsmembers.h>
#include <listssubscriptions.h>
#include <list.h> // TODO ?

// Saved Searches
#include <savedsearches.h>

// Places & Geo
#include <reversegeocode.h>
#include <geosearch.h>

// Trends
#include <place.h>
#include <available.h>

// Spam Reporting

// OAuth
#include <oauth.h>

// Help
#include <configuration.h>
#include <languages.h>
#include <privacy.h>
#include <tos.h>
#include <applicationratelimitstatus.h>

#include <oauthmanager.h>

#include <showrelatedresults.h>
#include <activitysummary.h>

#if QT_VERSION >= 0x050000
class QmlTwitterAPIPlugin : public QQmlExtensionPlugin
#else
class QmlTwitterAPIPlugin : public QDeclarativeExtensionPlugin
#endif
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
#endif
public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("TwitterAPI"));
        // @uri TwitterAPI

        int major = 1;
        int minor = 1;

        // Timelines
        qmlRegisterType<MentionsTimeline>(uri, major, minor, "MentionsTimelineModel");
        qmlRegisterType<UserTimeline>(uri, major, minor, "UserTimelineModel");
        qmlRegisterType<HomeTimeline>(uri, major, minor, "HomeTimelineModel");
        qmlRegisterType<RetweetsOfMe>(uri, major, minor, "RetweetsOfMeModel");

        // Tweets
        qmlRegisterType<Retweets>(uri, major, minor, "RetweetsModel");
        qmlRegisterType<Status>(uri, major, minor, "Status");

        // Search
        qmlRegisterType<Search>(uri, major, minor, "SearchModel");

        // Streaming
        qmlRegisterType<UserStream>(uri, major, minor, "UserStreamModel");
        qmlRegisterType<FilterStream>(uri, major, minor, "FilterStreamModel");
        qmlRegisterType<SampleStream>(uri, major, minor, "SampleStreamModel");

        // Direct Messages
        qmlRegisterType<DirectMessages>(uri, major, minor, "DirectMessagesModel");
        qmlRegisterType<DirectMessagesSent>(uri, major, minor, "DirectMessagesSentModel");
        qmlRegisterType<DirectMessage>(uri, major, minor, "DirectMessage");

        // Friends & Followers
        qmlRegisterType<NoRetweetsIds>(uri, major, minor, "NoRetweetsIdsModel");
        qmlRegisterType<FriendsIds>(uri, major, minor, "FriendsIdsModel");
        qmlRegisterType<FollowersIds>(uri, major, minor, "FollowersIdsModel");
        qmlRegisterType<Incoming>(uri, major, minor, "IncomingModel");
        qmlRegisterType<Outgoing>(uri, major, minor, "OutgoingModel");
        qmlRegisterType<ShowFriendships>(uri, major, minor, "ShowFriendships");
        qmlRegisterType<Friends>(uri, major, minor, "FriendsModel");
        qmlRegisterType<Followers>(uri, major, minor, "FollowersModel");



        qmlRegisterType<LookupUsers>(uri, major, minor, "UsersModel");
        qmlRegisterType<User>(uri, major, minor, "User");
        qmlRegisterType<Slugs>(uri, major, minor, "SlugsModel");
        qmlRegisterType<Suggestions>(uri, major, minor, "SuggestionsModel");
        qmlRegisterType<SearchUsers>(uri, major, minor, "SearchUsersModel");

        qmlRegisterType<FavoritesList>(uri, major, minor, "FavoritesModel");

        qmlRegisterType<Lists>(uri, major, minor, "ListsModel");
        qmlRegisterType<ListsSubscriptions>(uri, major, minor, "ListsSubscriptionsModel");
        qmlRegisterType<ListsMemberships>(uri, major, minor, "ListsMembershipsModel");
        qmlRegisterType<ListsStatuses>(uri, major, minor, "ListsStatusesModel");
        qmlRegisterType<ListsMembers>(uri, major, minor, "ListsMembersModel");
        qmlRegisterType<List>(uri, major, minor, "List");

        qmlRegisterType<VerifyCredentials>(uri, major, minor, "VerifyCredentials");
        qmlRegisterType<UpdateProfile>(uri, major, minor, "UpdateProfile");
        qmlRegisterType<Settings>(uri, major, minor, "Settings");
        qmlRegisterType<ApplicationRateLimitStatus>(uri, major, minor, "ApplicationRateLimitStatus");

        qmlRegisterType<SavedSearches>(uri, major, minor, "SavedSearchesModel");

        qmlRegisterType<GeoSearch>(uri, major, minor, "GeoSearchModel");
        qmlRegisterType<ReverseGeocode>(uri, major, minor, "ReverseGeocodeModel");

        qmlRegisterType<Place>(uri, major, minor, "TrendsPlaceModel");
        qmlRegisterType<Available>(uri, major, minor, "TrendsAvailableModel");

        qmlRegisterType<OAuth>(uri, major, minor, "OAuth");

        qmlRegisterType<Configuration>(uri, major, minor, "Configuration");
        qmlRegisterType<Languages>(uri, major, minor, "LanguagesModel");

        qmlRegisterType<Privacy>(uri, major, minor, "Privacy");
        qmlRegisterType<Tos>(uri, major, minor, "Tos");

        qmlRegisterType<ShowRelatedResults>(uri, major, minor, "RelatedResultsModel");
        qmlRegisterType<ActivitySummary>(uri, major, minor, "ActivitySummary");
    }
};

#include "main.moc"

#if QT_VERSION >= 0x050000
#else
Q_EXPORT_PLUGIN2(qmlTwitterAPIPlugin, QT_PREPEND_NAMESPACE(QmlTwitterAPIPlugin));
#endif
