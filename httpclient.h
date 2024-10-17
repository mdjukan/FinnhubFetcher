#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QUrl>
#include <QObject>
#include <QEventLoop>

class HttpClient : public QObject
{
    Q_OBJECT
public:
    HttpClient(QObject *parent = nullptr);
    QJsonDocument *makeRequest(const QUrl &url); //blokirajuci req
private:
    QEventLoop *m_event_loop;
    QNetworkAccessManager *m_manager;
};

#endif // HTTPCLIENT_H
