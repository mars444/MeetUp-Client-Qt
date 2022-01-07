#ifndef googleAuth_H
#define googleAuth_H

#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QNetworkReply>

class googleAuth : public QObject
{
    Q_OBJECT
public:
    explicit googleAuth(QObject *parent = nullptr);

private:
    QOAuth2AuthorizationCodeFlow * google;
};

#endif // googleAuth_H
