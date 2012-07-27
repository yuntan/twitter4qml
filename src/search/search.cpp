#include "search.h"
#include "../utils.h"

class Search::Private
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
    QString maxIdStr;
    QString nextPage;
    QString refreshUrl;
};

Search::Private::Private()
    : page(0)
    , resultType("mixed")
    , rpp(0)
    , showUser(false)
    , includeEntities(true)
{
}

Search::Search(QObject *parent)
    : AbstractTwitterModel(parent)
    , d(new Private)
{
    QHash<int, QByteArray> roles;
    roles[CreatedAtRole] = "created_at";
    roles[FromUserRole] = "from_user";
    roles[FromUserIdRole] = "from_user_id_str";
    roles[FromUserNameRole] = "from_user_name";
    roles[IdRole] = "id";
    roles[IdStrRole] = "id_str";
    roles[InReplyToStatusIdRole] = "in_reply_to_status_id_str";
    roles[IsoLanguageCodeRole] = "iso_language_code";
    roles[MetadataRole] = "metadata";
    roles[ProfileImageUrlRole] = "profile_image_url";
    roles[ProfileImageUrlHttpsRole] = "profile_image_url_https";
    roles[SourceRole] = "source";
    roles[TextRole] = "text";
    roles[PlainTextRole] = "plain_text";
    roles[ToUserRole] = "to_user";
    roles[ToUserIdRole] = "to_user_id_str";
    roles[ToUserNameRole] = "to_user_name";
    setRoleNames(roles);

    connect(this, SIGNAL(qChanged(QString)), this, SLOT(reload()));
    connect(this, SIGNAL(geocodeChanged(QString)), this, SLOT(reload()));
}

Search::~Search()
{
    delete d;
}

void Search::reload()
{
    if (q().isEmpty() && geocode().isEmpty()) return;
    AbstractTwitterModel::reload();
}

void Search::parseDone(const QVariant &result)
{
    if (result.type() == QVariant::Map) {
        QVariantMap object = result.toMap();
        if (object.contains("completed_in"))
            setCompletedIn(object.value("completed_in").toFloat());
        if (object.contains("max_id_str"))
            setMaxIdStr(object.value("max_id_str").toString());
        if (object.contains("next_page"))
            setNextPage(object.value("next_page").toString());
        if (object.contains("page"))
            setPage(object.value("page").toInt());
        if (object.contains("query"))
            setQ(object.value("query").toString());
        if (object.contains("refresh_url"))
            setRefreshUrl(object.value("refresh_url").toString());
        if (object.contains("results") && object.value("results").type() == QVariant::List) {
            QVariantList results = object.value("results").toList();
            foreach (const QVariant &result, results) {
                if (result.type() == QVariant::Map) {
                    QVariantMap map = Search::parse(result.toMap());
                    addData(map);
                }
            }
        }
    }
}

void Search::dataAdded(const QString &key, const QVariantMap &value)
{
    Q_UNUSED(key)
    if (value.value("text").toString().contains(q())) {
        addData(value);
    }
}

const QString &Search::q() const
{
    return d->query;
}

void Search::setQ(const QString &q)
{
    if (d->query == q) return;
    d->query = q;
    emit qChanged(q);
}

const QString &Search::geocode() const
{
    return d->geocode;
}

void Search::setGeocode(const QString &geocode)
{
    if (d->geocode == geocode) return;
    d->geocode = geocode;
    emit geocodeChanged(geocode);
}

const QString &Search::lang() const
{
    return d->lang;
}

void Search::setLang(const QString &lang)
{
    if (d->lang == lang) return;
    d->lang = lang;
    emit langChanged(lang);
}

const QString &Search::locale() const
{
    return d->locale;
}

void Search::setLocale(const QString &locale)
{
    if (d->locale == locale) return;
    d->locale = locale;
    emit localeChanged(locale);
}

int Search::page() const
{
    return d->page;
}

void Search::setPage(int page)
{
    if (d->page == page) return;
    d->page = page;
    emit pageChanged(page);
}

const QString &Search::resultType() const
{
    return d->resultType;
}

void Search::setResultType(const QString &resultType)
{
    if (d->resultType == resultType) return;
    d->resultType = resultType;
    emit resultTypeChanged(resultType);
}

int Search::rpp() const
{
    return d->rpp;
}

void Search::setRpp(int rpp)
{
    if (d->rpp == rpp) return;
    d->rpp = rpp;
    emit rppChanged(rpp);
}

bool Search::showUser() const
{
    return d->showUser;
}

void Search::setShowUser(bool showUser)
{
    if (d->showUser == showUser) return;
    d->showUser = showUser;
    emit showUserChanged(showUser);
}

const QString &Search::until() const
{
    return d->until;
}

void Search::setUntil(const QString &until)
{
    if (d->until == until) return;
    d->until = until;
    emit untilChanged(until);
}

const QString &Search::sinceId() const
{
    return d->sinceId;
}

void Search::setSinceId(const QString &sinceId)
{
    if (d->sinceId == sinceId) return;
    d->sinceId = sinceId;
    emit sinceIdChanged(sinceId);
}

bool Search::includeEntities() const
{
    return d->includeEntities;
}

void Search::setIncludeEntities(bool includeEntities)
{
    if (d->includeEntities == includeEntities) return;
    d->includeEntities = includeEntities;
    emit includeEntitiesChanged(includeEntities);
}

float Search::completedIn() const
{
    return d->completedIn;
}

void Search::setCompletedIn(float completedIn)
{
    if (d->completedIn == completedIn) return;
    d->completedIn = completedIn;
    emit completedInChanged(completedIn);
}

const QString &Search::maxIdStr() const
{
    return d->maxIdStr;
}

void Search::setMaxIdStr(const QString &maxIdStr)
{
    if (d->maxIdStr == maxIdStr) return;
    d->maxIdStr = maxIdStr;
    emit maxIdStrChanged(maxIdStr);
}

const QString &Search::nextPage() const
{
    return d->nextPage;
}

void Search::setNextPage(const QString &nextPage)
{
    if (d->nextPage == nextPage) return;
    d->nextPage = nextPage;
    emit nextPageChanged(nextPage);
}

const QString &Search::refreshUrl() const
{
    return d->refreshUrl;
}

void Search::setRefreshUrl(const QString &refreshUrl)
{
    if (d->refreshUrl == refreshUrl) return;
    d->refreshUrl = refreshUrl;
    emit refreshUrlChanged(refreshUrl);
}

bool Search::indicesGreaterThan(const QVariant &v1, const QVariant &v2)
{
    return v1.toMap().value("indices").toList().first().toInt() > v2.toMap().value("indices").toList().first().toInt();
}

QVariantMap Search::parse(const QVariantMap &status)
{
    QVariantMap ret = status;

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
        qSort(entitiesSortedByIndices.begin(), entitiesSortedByIndices.end(), &Search::indicesGreaterThan);
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
                    richTextAfter = QString("<a class=\"link\" href=\"%1\" title=\"%2\">%3</a>")
                            .arg(entity.value("expanded_url").toString())
                            .arg(entity.value("url").toString())
                            .arg(entity.value("display_url").toString());
                } else {
                    plainTextAfter = entity.value("url").toString();
                    richTextAfter = QString("<a class=\"link\" href=\"%1\" title=\"%1\">%1</a>")
                            .arg(entity.value("url").toString());
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
                richTextAfter = QString("<a class=\"media\" href=\"%1\" title=\"%2\">%3</a>")
                        .arg(entity.value("media_url").toString())
                        .arg(entity.value("url").toString())
                        .arg(entity.value("display_url").toString());
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
