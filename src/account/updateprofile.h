#ifndef UPDATEPROFILE_H
#define UPDATEPROFILE_H

#include "../tools/abstracttwitteraction.h"

class UpdateProfile : public AbstractTwitterAction
{
    Q_OBJECT
    Q_DISABLE_COPY(UpdateProfile)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool include_entities READ includeEntities WRITE setIncludeEntities NOTIFY includeEntitiesChanged)
    Q_PROPERTY(bool skip_status READ skipStatus WRITE setSkipStatus NOTIFY skipStatusChanged)
public:
    explicit UpdateProfile(QObject *parent = 0);
    ~UpdateProfile();

    const QString &name() const;
    void setName(const QString &name);
    const QString &url() const;
    void setUrl(const QString &url);
    const QString &location() const;
    void setLocation(const QString &location);
    const QString &description() const;
    void setDescription(const QString &description);
    bool includeEntities() const;
    void setIncludeEntities(bool includeEntities);
    bool skipStatus() const;
    void setSkipStatus(bool skipStatus);

signals:
    void nameChanged(const QString &name);
    void urlChanged(const QString &url);
    void locationChanged(const QString &location);
    void descriptionChanged(const QString &description);
    void includeEntitiesChanged(bool includeEntities);
    void skipStatusChanged(bool skipStatus);

protected:
    QUrl api() const { return QUrl("http://api.twitter.com/1/account/update_profile.json"); }

private:
    class Private;
    Private *d;
};

#endif // UPDATEPROFILE_H
