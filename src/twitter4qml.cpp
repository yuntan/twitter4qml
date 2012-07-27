#include "twitter4qml.h"
#include <QtDeclarative/qdeclarative.h>

#include "streaming/userstream.h"
#include "streaming/filterstream.h"

#include "statuses/hometimeline.h"
#include "statuses/mentions.h"
#include "statuses/publictimeline.h"
#include "statuses/retweetedbyme.h"
#include "statuses/retweetedtome.h"
#include "statuses/retweetsofme.h"
#include "statuses/usertimeline.h"
#include "statuses/retweetedtouser.h"
#include "statuses/retweetedbyuser.h"
#include "statuses/retweetedby.h"
#include "statuses/retweetedbyids.h"
#include "statuses/retweets.h"
#include "statuses/status.h"

#include "search/search.h"
#include "search/searchstatuses.h"

#include "directmessages/directmessages.h"
#include "directmessages/directmessagessent.h"
#include "directmessages/directmessage.h"

#include "friendships/followers.h"
#include "friendships/friends.h"
#include "friendships/incoming.h"
#include "friendships/outgoing.h"
#include "friendships/showfriendships.h"
#include "friendships/noretweetids.h"

#include "users/lookupusers.h"
#include "users/user.h"
#include "users/slugs.h"
#include "users/suggestions.h"
#include "users/searchusers.h"

#include "favorites/favorites.h"

#include "lists/lists.h"
#include "lists/listsall.h"
#include "lists/listssubscriptions.h"
#include "lists/listsmemberships.h"
#include "lists/liststatuses.h"
#include "lists/listmembers.h"
#include "lists/list.h"

#include "account/verifycredentials.h"
#include "account/updateprofile.h"
#include "account/totals.h"
#include "account/settings.h"
#include "account/ratelimitstatus.h"

#include "savedsearches/savedsearches.h"

#include "geo/geosearch.h"
#include "geo/reversegeocode.h"

#include "trends/trends.h"
#include "trends/available.h"
#include "trends/daily.h"
#include "trends/weekly.h"

#include "oauth/oauth.h"

#include "extra/unionmodel.h"

#include "tools/oauthmanager.h"

#include "help/configuration.h"
#include "help/test.h"
#include "help/languages.h"

#include "legal/privacy.h"
#include "legal/tos.h"

#include "related_results/showrelatedresults.h"
#include "statuses/activitysummary.h"

Twitter4QML::Twitter4QML(QObject *parent)
    : QObject(parent)
{
    qmlRegisterUncreatableType<Twitter4QML>("Twitter4QML", 1, 0, "Twitter4QML", "access twitter4qml directly.");

    qmlRegisterType<UserStream>("Twitter4QML", 1, 0, "UserStreamModel");
    qmlRegisterType<FilterStream>("Twitter4QML", 1, 0, "FilterStreamModel");

    qmlRegisterType<HomeTimeline>("Twitter4QML", 1, 0, "HomeTimelineModel");
    qmlRegisterType<Mentions>("Twitter4QML", 1, 0, "MentionsModel");
    qmlRegisterType<PublicTimeline>("Twitter4QML", 1, 0, "PublicTimelineModel");
    qmlRegisterType<RetweetedByMe>("Twitter4QML", 1, 0, "RetweetedByMeModel");
    qmlRegisterType<RetweetedToMe>("Twitter4QML", 1, 0, "RetweetedToMeModel");
    qmlRegisterType<RetweetsOfMe>("Twitter4QML", 1, 0, "RetweetsOfMeModel");
    qmlRegisterType<UserTimeline>("Twitter4QML", 1, 0, "UserTimelineModel");
    qmlRegisterType<RetweetedToUser>("Twitter4QML", 1, 0, "RetweetedToUserModel");
    qmlRegisterType<RetweetedByUser>("Twitter4QML", 1, 0, "RetweetedByUserModel");
    qmlRegisterType<RetweetedBy>("Twitter4QML", 1, 0, "RetweetedByModel");
    qmlRegisterType<RetweetedByIds>("Twitter4QML", 1, 0, "RetweetedByIdsModel");
    qmlRegisterType<Retweets>("Twitter4QML", 1, 0, "RetweetsModel");
    qmlRegisterType<Status>("Twitter4QML", 1, 0, "Status");

    qmlRegisterType<DirectMessages>("Twitter4QML", 1, 0, "DirectMessagesModel");
    qmlRegisterType<DirectMessagesSent>("Twitter4QML", 1, 0, "DirectMessagesSentModel");
    qmlRegisterType<DirectMessage>("Twitter4QML", 1, 0, "DirectMessage");

    qmlRegisterType<Search>("Twitter4QML", 1, 0, "SearchModel");
    qmlRegisterType<SearchStatuses>("Twitter4QML", 1, 0, "SearchStatusesModel");

    qmlRegisterType<Followers>("Twitter4QML", 1, 0, "FollowersModel");
    qmlRegisterType<Friends>("Twitter4QML", 1, 0, "FriendsModel");
    qmlRegisterType<Incoming>("Twitter4QML", 1, 0, "IncomingModel");
    qmlRegisterType<Outgoing>("Twitter4QML", 1, 0, "OutgoingModel");
    qmlRegisterType<ShowFriendships>("Twitter4QML", 1, 0, "ShowFriendships");
    qmlRegisterType<NoRetweetIds>("Twitter4QML", 1, 0, "NoRetweetIdsModel");

    qmlRegisterType<LookupUsers>("Twitter4QML", 1, 0, "UsersModel");
    qmlRegisterType<User>("Twitter4QML", 1, 0, "User");
    qmlRegisterType<Slugs>("Twitter4QML", 1, 0, "SlugsModel");
    qmlRegisterType<Suggestions>("Twitter4QML", 1, 0, "SuggestionsModel");
    qmlRegisterType<SearchUsers>("Twitter4QML", 1, 0, "SearchUsersModel");

    qmlRegisterType<Favorites>("Twitter4QML", 1, 0, "FavoritesModel");

    qmlRegisterType<ListsAll>("Twitter4QML", 1, 0, "ListsAllModel");
    qmlRegisterType<Lists>("Twitter4QML", 1, 0, "ListsModel");
    qmlRegisterType<ListsSubscriptions>("Twitter4QML", 1, 0, "ListsSubscriptionsModel");
    qmlRegisterType<ListsMemberships>("Twitter4QML", 1, 0, "ListsMembershipsModel");
    qmlRegisterType<ListStatuses>("Twitter4QML", 1, 0, "ListStatusesModel");
    qmlRegisterType<ListMembers>("Twitter4QML", 1, 0, "ListMembersModel");
    qmlRegisterType<List>("Twitter4QML", 1, 0, "List");

    qmlRegisterType<VerifyCredentials>("Twitter4QML", 1, 0, "VerifyCredentials");
    qmlRegisterType<UpdateProfile>("Twitter4QML", 1, 0, "UpdateProfile");
    qmlRegisterType<Totals>("Twitter4QML", 1, 0, "Totals");
    qmlRegisterType<Settings>("Twitter4QML", 1, 0, "Settings");
    qmlRegisterType<RateLimitStatus>("Twitter4QML", 1, 0, "RateLimitStatus");

    qmlRegisterType<SavedSearches>("Twitter4QML", 1, 0, "SavedSearchesModel");

    qmlRegisterType<GeoSearch>("Twitter4QML", 1, 0, "GeoSearchModel");
    qmlRegisterType<ReverseGeocode>("Twitter4QML", 1, 0, "ReverseGeocodeModel");

    qmlRegisterType<Trends>("Twitter4QML", 1, 0, "TrendsModel");
    qmlRegisterType<Available>("Twitter4QML", 1, 0, "AvailableModel");
    qmlRegisterType<Daily>("Twitter4QML", 1, 0, "DailyModel");
    qmlRegisterType<Weekly>("Twitter4QML", 1, 0, "WeeklyModel");

    qmlRegisterType<OAuth>("Twitter4QML", 1, 0, "OAuth");

    qmlRegisterType<Configuration>("Twitter4QML", 1, 0, "Configuration");
    qmlRegisterType<Test>("Twitter4QML", 1, 0, "Test");
    qmlRegisterType<Languages>("Twitter4QML", 1, 0, "LanguagesModel");

    qmlRegisterType<Privacy>("Twitter4QML", 1, 0, "Privacy");
    qmlRegisterType<Tos>("Twitter4QML", 1, 0, "Tos");

    qmlRegisterType<ShowRelatedResults>("Twitter4QML", 1, 0, "RelatedResultsModel");
    qmlRegisterType<ActivitySummary>("Twitter4QML", 1, 0, "ActivitySummary");

    qmlRegisterType<UnionModel>("Twitter4QML.extra", 1, 0, "UnionModel");
}

QNetworkAccessManager *Twitter4QML::networkAccessManager() const
{
    return OAuthManager::instance().networkAccessManager();
}

void Twitter4QML::setNetworkAccessManager(QNetworkAccessManager *networkAccessManager)
{
    OAuthManager::instance().setNetworkAccessManager(networkAccessManager);
}
