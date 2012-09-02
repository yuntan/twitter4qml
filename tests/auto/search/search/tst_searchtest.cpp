#include <QtCore/QString>
#include <QtCore/QTime>
#include <QtTest/QtTest>

#include <oauth/oauth.h>
#include <search/search.h>

class SearchTest : public QObject
{
    Q_OBJECT
    
public:
    SearchTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    void q();
    void q_data();

private:
    Search *search;
};

SearchTest::SearchTest()
{
    OAuth oauth;
    oauth.setConsumerKey(QLatin1String("K6eWjgzGz1qE4oOOBYkdMg"));
    oauth.setConsumerSecret(QLatin1String("t4ku8EEo8Sw7ywZ26vAxuQuH7sH0CQYH4DvhizEX4"));
    oauth.setToken(QLatin1String("798286350-Za9khIT9UFYdNKMwjuha1zyrbeiVInr2p8iLtetk"));
    oauth.setTokenSecret(QLatin1String("xfGg5t21TmJQdxxOpD4KYaxjRUZgIf8KIV33Z9s"));
}

void SearchTest::init()
{
    search = new Search(this);
}

void SearchTest::cleanup()
{
    delete search;
    search = 0;
}

void SearchTest::q()
{
    QFETCH(QString, query);

    search->setQ(query);

    QCOMPARE(search->q(), query);
    QCOMPARE(search->isLoading(), true);

    QTime timer;
    timer.start();
    forever {
        if (!search->isLoading()) break;
        if (timer.elapsed() > 1000 * 30) QFAIL("Timeout");
        QTest::qWait(100);
    }

    QVERIFY2(search->rowCount() > 0, "Empty");
}

void SearchTest::q_data()
{
    QTest::addColumn<QString>("query");
    QTest::newRow("Twitter") << QString("Twitter");
    QTest::newRow("#Qt") << QString("#Qt");
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    SearchTest search;
    return QTest::qExec(&search, argc, argv);
}

#include "tst_searchtest.moc"
