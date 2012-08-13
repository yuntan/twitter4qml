#include "searchstatuses.h"
#include "../statuses/showstatus.h"
#include "../statuses/status.h"
#include "../utils.h"
#include <QtCore/QQueue>

class SearchStatuses::Private
{
public:
    Private();

    QString query;
    QString geocode;
    QString lang;
    QString locale;
    int page;
    QString resultType;
    int rpp;
    bool showUser;
    QString until;
    QString sinceId;
    bool includeEntities;

    float completedIn;
    QString nextPage;
    QString refreshUrl;
};

SearchStatuses::Private::Private()
    : page(0)
    , resultType("mixed")
    , rpp(0)
    , showUser(false)
    , includeEntities(true)
{
}

SearchStatuses::SearchStatuses(QObject *parent)
    : AbstractStatusesModel(parent)
    , d(new Private)
{
}

SearchStatuses::~SearchStatuses()
{
    delete d;
}

void SearchStatuses::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::Map) {
        QVariantMap object = result.toMap();
        if (object.contains("completed_in"))
            setCompletedIn(object.value("completed_in").toFloat());
        if (object.contains("max_id_str"))
            setMaxId(object.value("max_id_str").toString());
        if (object.contains("next_page"))
            setNextPage(object.value("next_page").toString());
        if (object.contains("page"))
            setPage(object.value("page").toInt());
//        if (object.contains("query"))
//            setQ(object.value("query").toString());
        if (object.contains("refresh_url"))
            setRefreshUrl(object.value("refresh_url").toString());
        if (object.contains("results") && object.value("results").type() == QVariant::List) {
            QVariantList results = object.value("results").toList();
            if (results.isEmpty()) {
                emit loadingChanged(false);
            } else {
                foreach (const QVariant &result, results) {
                    if (result.type() == QVariant::Map) {
                        QVariantMap map = SearchStatuses::parse(result.toMap());
                        addData(map);
                    }
                }
            }
        } else {
            DEBUG() << object;
        }
    }
}

void SearchStatuses::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (value.value("text").toString().contains(QString(QByteArray::fromPercentEncoding(q().toUtf8())), Qt::CaseInsensitive)) {
        addData(value);
    }
}

const QString &SearchStatuses::q() const
{
    return d->query;
}

void SearchStatuses::setQ(const QString &q)
{
    if (d->query == q) return;
    d->query = q;
    emit qChanged(q);
}

const QString &SearchStatuses::geocode() const
{
    return d->geocode;
}

void SearchStatuses::setGeocode(const QString &geocode)
{
    if (d->geocode == geocode) return;
    d->geocode = geocode;
    emit geocodeChanged(geocode);
}

const QString &SearchStatuses::lang() const
{
    return d->lang;
}

void SearchStatuses::setLang(const QString &lang)
{
    if (d->lang == lang) return;
    d->lang = lang;
    emit langChanged(lang);
}

const QString &SearchStatuses::locale() const
{
    return d->locale;
}

void SearchStatuses::setLocale(const QString &locale)
{
    if (d->locale == locale) return;
    d->locale = locale;
    emit localeChanged(locale);
}

const QString &SearchStatuses::resultType() const
{
    return d->resultType;
}

void SearchStatuses::setResultType(const QString &resultType)
{
    if (d->resultType == resultType) return;
    d->resultType = resultType;
    emit resultTypeChanged(resultType);
}

bool SearchStatuses::showUser() const
{
    return d->showUser;
}

void SearchStatuses::setShowUser(bool showUser)
{
    if (d->showUser == showUser) return;
    d->showUser = showUser;
    emit showUserChanged(showUser);
}

const QString &SearchStatuses::until() const
{
    return d->until;
}

void SearchStatuses::setUntil(const QString &until)
{
    if (d->until == until) return;
    d->until = until;
    emit untilChanged(until);
}

float SearchStatuses::completedIn() const
{
    return d->completedIn;
}

void SearchStatuses::setCompletedIn(float completedIn)
{
    if (d->completedIn == completedIn) return;
    d->completedIn = completedIn;
    emit completedInChanged(completedIn);
}

const QString &SearchStatuses::nextPage() const
{
    return d->nextPage;
}

void SearchStatuses::setNextPage(const QString &nextPage)
{
    if (d->nextPage == nextPage) return;
    d->nextPage = nextPage;
    emit nextPageChanged(nextPage);
}

const QString &SearchStatuses::refreshUrl() const
{
    return d->refreshUrl;
}

void SearchStatuses::setRefreshUrl(const QString &refreshUrl)
{
    if (d->refreshUrl == refreshUrl) return;
    d->refreshUrl = refreshUrl;
    emit refreshUrlChanged(refreshUrl);
}

bool SearchStatuses::indicesGreaterThan(const QVariant &v1, const QVariant &v2)
{
    return v1.toMap().value("indices").toList().first().toInt() > v2.toMap().value("indices").toList().first().toInt();
}

QVariantMap SearchStatuses::parse(const QVariantMap &status)
{
    QVariantMap ret = status;

    QVariantMap user;
    user.insert("screen_name", ret.value("from_user").toString());
    user.insert("id", ret.value("from_user_id").toLongLong());
    user.insert("id_str", ret.value("from_user_id_str").toString());
    user.insert("name", ret.value("from_user_name").toString());
    user.insert("profile_image_url", ret.value("profile_image_url").toString());
    user.insert("profile_image_url_https", ret.value("profile_image_url_https").toString());
    ret.remove("from_user");
    ret.remove("from_user_id");
    ret.remove("from_user_id_str");
    ret.remove("from_user_name");
    ret.remove("profile_image_url");
    ret.remove("profile_image_url_https");

    ret.insert("user", user);

    QString source = ret.value("source").toString();
    source.replace("&lt;", "<").replace("&gt;", ">").replace("&quat;", "\"");
    ret.insert("source", source);

    QString text = ret.value("text").toString();
    if (ret.contains("entities") && !ret.value("entities").isNull()) {
//        DEBUG() << text;
        QString plainText = text;
        QString richText = text.replace(" ", "\t");
        QVariantList entitiesSortedByIndices;
        QVariantMap entities = ret.value("entities").toMap();
        foreach (const QString &key, entities.keys()) {
            QVariant entity = entities.value(key);
            if (entity.type() == QVariant::List) {
                QVariantList e = entity.toList();
                foreach (const QVariant &ee, e) {
                    QVariantMap eee = ee.toMap();
                    eee.insert("type", key);
                    entitiesSortedByIndices.append(eee);
                }
            } else {
                DEBUG() << entity;
            }
        }
        qSort(entitiesSortedByIndices.begin(), entitiesSortedByIndices.end(), &SearchStatuses::indicesGreaterThan);
        QVariantList media;
        foreach (const QVariant &item, entitiesSortedByIndices) {
            QVariantMap entity = item.toMap();
            QVariantList indices = entity.value("indices").toList();
            int start = indices.first().toInt();
            int end = indices.last().toInt();
            QString type = entity.value("type").toString();
            QString plainTextAfter;
            QString richTextAfter;
            if (type == "urls") {
                if (entity.contains("display_url")) {
                    plainTextAfter = entity.value("display_url").toString();
                    richTextAfter = QString("<a class=\"link\" href=\"")
                            .append(entity.value("expanded_url").toString())
                            .append("\" title=\"")
                            .append(entity.value("url").toString())
                            .append("\">")
                            .append(entity.value("display_url").toString())
                            .append("</a>");
                } else {
                    plainTextAfter = entity.value("url").toString();
                    richTextAfter = QString("<a class=\"link\" href=\"")
                            .append(entity.value("url").toString())
                            .append("\" title=\"")
                            .append(entity.value("url").toString())
                            .append("\">")
                            .append(entity.value("url").toString())
                            .append("</a>");
                }
            } else if (type == "user_mentions") {
                richTextAfter = QString("<a class=\"screen_name\" href=\"user://%1\" title=\"@%2\">@%2</a>")
                        .arg(entity.value("id_str").toString())
                        .arg(entity.value("screen_name").toString());
            } else if (type == "hashtags") {
                richTextAfter = QString("<a class=\"hash_tag\" href=\"search://#%1\" title=\"#%2\">#%2</a>")
                        .arg(entity.value("text").toString())
                        .arg(entity.value("text").toString());
            } else if (type == "media") {
                plainTextAfter = entity.value("display_url").toString();
                richTextAfter = QString("<a class=\"media\" href=\"")
                        .append(entity.value("media_url").toString())
                        .append("\" title=\"")
                        .append(entity.value("url").toString())
                        .append("\">")
                        .append(entity.value("display_url").toString())
                        .append("</a>");
                media.append(entity.value("media_url"));
            } else {
                DEBUG() << type << item;
            }
            if (!plainTextAfter.isNull())
                plainText.replace(start, end - start, plainTextAfter);
            if (!richTextAfter.isNull())
                richText.replace(start, end - start, richTextAfter);
        }


//        DEBUG() << ret.value("text").toString();
        ret.insert("plain_text", escapeHtml(plainText));
//        DEBUG() << ret.value("plain_text").toString();
        ret.insert("rich_text", richText.replace("\n", "<br />").replace("\t", "&nbsp;").replace(QString::fromUtf8("　"), "&nbsp;&nbsp;&nbsp;&nbsp;"));
//        DEBUG() << ret.value("rich_text").toString();
        ret.insert("media", media);
    } else {
        DEBUG() << text;
        if (!ret.contains("plain_text"))
            ret.insert("plain_text", escapeHtml(text));
        if (!ret.contains("rich_text"))
            ret.insert("rich_text", text.replace(" ", "&nbsp;").replace("\n", "<br />").replace(QString::fromUtf8("　"), "&nbsp;&nbsp;&nbsp;&nbsp;"));
    }

    return ret;
}
