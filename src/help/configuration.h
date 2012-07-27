#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../tools/abstracttwitteraction.h"

class Configuration : public AbstractTwitterAction
{
    Q_OBJECT
    Q_PROPERTY(QString characters_reserved_per_media READ charactersReservedPerMedia WRITE setCharactersReservedPerMedia NOTIFY charactersReservedPerMediaChanged DESIGNABLE false USER true)
    Q_PROPERTY(QVariantList non_username_paths READ nonUsernamePaths WRITE setNonUsernamePath NOTIFY nonUsernamePathsChanged DESIGNABLE false USER true)
    Q_PROPERTY(int max_media_per_upload READ maxMediaPerUpload WRITE setMaxMediaPerUpload NOTIFY maxMediaPerUploadChanged DESIGNABLE false USER true)
    Q_PROPERTY(int photo_size_limit READ photoSizeLimit WRITE setPhotoSizeLimit NOTIFY photoSizeLimitChanged DESIGNABLE false USER true)
    Q_PROPERTY(int short_url_length READ shortUrlLength WRITE setShortUrlLength NOTIFY shortUrlLengthChanged DESIGNABLE false USER true)
    Q_PROPERTY(int short_url_length_https READ shortUrlLengthHttps WRITE setShortUrlLengthHttps NOTIFY shortUrlLengthHttpsChanged DESIGNABLE false USER true)
public:
    explicit Configuration(QObject *parent = 0);
    ~Configuration();

    const QString &charactersReservedPerMedia() const;
    void setCharactersReservedPerMedia(const QString &charactersReservedPerMedia);
    const QVariantList &nonUsernamePaths() const;
    void setNonUsernamePath(const QVariantList &nonUsernamePaths);
    int maxMediaPerUpload() const;
    void setMaxMediaPerUpload(int maxMediaPerUpload);
    int photoSizeLimit() const;
    void setPhotoSizeLimit(int photoSizeLimit);
    int shortUrlLength() const;
    void setShortUrlLength(int shortUrlLength);
    int shortUrlLengthHttps() const;
    void setShortUrlLengthHttps(int shortUrlLengthHttps);

signals:
    void charactersReservedPerMediaChanged(const QString &charactersReservedPerMedia);
    void nonUsernamePathsChanged(const QVariantList &nonUsernamePaths);
    void maxMediaPerUploadChanged(int maxMediaPerUpload);
    void photoSizeLimitChanged(int photoSizeLimit);
    void shortUrlLengthChanged(int shortUrlLength);
    void shortUrlLengthHttpsChanged(int shortUrlLengthHttps);

protected:
    AuthorizeBy authenticationMethod() const { return AuthorizeByUrl; }
    QString httpMethod() const { return "GET"; }
    QUrl api() const { return QUrl("http://api.twitter.com/1/help/configuration.json"); }

private:
    class Private;
    Private *d;
};

#endif // CONFIGURATION_H
