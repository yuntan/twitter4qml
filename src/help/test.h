#ifndef TEST_H
#define TEST_H

#include "../tools/abstracttwitteraction.h"

class Test : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(bool ok READ isOk NOTIFY isOkChanged DESIGNABLE false USER true)

public:
    explicit Test(QObject *parent = 0);
    ~Test();

    bool isOk() const;

signals:
    void isOkChanged(bool isOk);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByNothing; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("http://api.twitter.com/1/help/test.json"); }
    void setData(const QVariant &data);

private:
    class Private;
    Private *d;
};

#endif // TEST_H
