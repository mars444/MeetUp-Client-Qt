//#include "googleauth.h"
//#include <QObject>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonArray>
//#include <QString>
//#include <QFile>
//#include <QDir>
//#include <QUrl>
//#include <QOAuthHttpServerReplyHandler>
//#include <QDesktopServices>


//googleAuth::googleAuth(QObject *parent) : QObject(parent)
//{
//    this->google = new QOAuth2AuthorizationCodeFlow(this);
//    this->google->setScope("email");

//    connect(this->google, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);

//    QByteArray val;
//    QFile file;
//    file.setFileName(QDir::toNativeSeparators(":/resc/resc/client_secret_googleusercontent.com.json"));
//    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        val = file.readAll();
//        file.close();
//    }


//    QJsonDocument document = QJsonDocument::fromJson(val);
//    QJsonObject object = document.object();
//    const auto settingsObject = object["web"].toObject();
//    const QUrl authUri(settingsObject["auth_uri"].toString());
//    const auto clientId = settingsObject["client_id"].toString();
//    const QUrl tokenUri(settingsObject["token_uri"].toString());
//    const auto clientSecret(settingsObject["client_secret"].toString());

//    const auto redirectUris = settingsObject["redirect_uris"].toArray();
//    const QUrl redirectUri(redirectUris[0].toString());
//    const auto port = static_cast<quint16>(redirectUri.port());

//    this->google->setAuthorizationUrl(authUri);
//    this->google->setClientIdentifier(clientId);
//    this->google->setAccessTokenUrl(tokenUri);
//    this->google->setClientIdentifierSharedKey(clientSecret);

//    auto replyHandler = new QOAuthHttpServerReplyHandler(port, this);
//    this->google->setReplyHandler(replyHandler);
//    this->google->grant();

//    connect(this->google, &QOAuth2AuthorizationCodeFlow::granted, [=](){
//        qDebug() << __FUNCTION__ << __LINE__ << "Access Granted!";
//        auto reply = this->google->get(QUrl("https://www.googleapis.com/plus/v1/people/me"));
//        connect(reply, &QNetworkReply::finished, [reply](){
//            qDebug() << "REQUEST FINISHED. Error? " << (reply->error() != QNetworkReply::NoError);
//            qDebug() << reply->readAll();
//        });
//    });
//}
