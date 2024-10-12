#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QObject>

class HttpClient : public QObject
{
    Q_OBJECT
public:
    HttpClient(QObject *parent = nullptr);
    void makeRequest(const QUrl &url);
    void handleResponse(QNetworkReply *reply);    void parseJson(const QByteArray &data);
private:
    QNetworkAccessManager *m_manager;
};

#endif // HTTPCLIENT_H
