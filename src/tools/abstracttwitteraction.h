#ifndef ABSTRACTTWITTERACTION_H
#define ABSTRACTTWITTERACTION_H

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVariantMap>

class AbstractTwitterAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged DESIGNABLE false)
    Q_PROPERTY(QVariant data READ data NOTIFY dataChanged DESIGNABLE false)
    Q_DISABLE_COPY(AbstractTwitterAction)
public:
    enum AuthorizeBy {
        AuthorizeByNothing,
        AuthorizeByHeader,
        AuthorizeByBody,
        AuthorizeByUrl
    };
    explicit AbstractTwitterAction(QObject *parent = 0);

    bool isLoading() const;
    const QVariant &data() const;

public slots:
    virtual void exec();

signals:
    void loadingChanged(bool isLoading);
    void dataChanged(const QVariant &data);

protected slots:
    void setParameters(const QVariantMap &parameters);

protected:
    void setLoading(bool isLoading);
    virtual void setData(const QVariant &data);

    virtual QUrl api() const = 0;
    virtual bool isMultiPart() const { return false; }
    virtual AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    virtual QString httpMethod() const { return "POST"; }

private:
    class Private;
    Private *d;
};

#endif // ABSTRACTTWITTERACTION_H
