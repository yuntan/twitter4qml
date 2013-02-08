#include <QtCore/qglobal.h>

#if QT_VERSION >= 0x050000
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#else
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#endif

#include <twitter4qml.h>
#include <oauth/oauth.h>
#include <tools/oauthmanager.h>

int main(int argc, char **argv)
{
#if QT_VERSION >= 0x050000
    QGuiApplication app(argc, argv);
#else
    QApplication app(argc, argv);
#endif

    Twitter4QML twitter4qml;
    OAuth oauth;
    oauth.setConsumerKey(QLatin1String("K6eWjgzGz1qE4oOOBYkdMg"));
    oauth.setConsumerSecret(QLatin1String("t4ku8EEo8Sw7ywZ26vAxuQuH7sH0CQYH4DvhizEX4"));
    oauth.setToken(QLatin1String("798286350-Za9khIT9UFYdNKMwjuha1zyrbeiVInr2p8iLtetk"));
    oauth.setTokenSecret(QLatin1String("xfGg5t21TmJQdxxOpD4KYaxjRUZgIf8KIV33Z9s"));
    OAuthManager::instance().setAuthorized(true);

#if QT_VERSION >= 0x050000
    QQuickView view;
    view.setSource(QUrl("qrc:/2.x/main.qml"));
#else
    QDeclarativeView view;
    view.setSource(QUrl("qrc:/1.x/main.qml"));
#endif
    view.show();

    return app.exec();
}

