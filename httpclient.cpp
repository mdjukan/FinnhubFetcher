#include "httpclient.h"
#include <QEventLoop>

HttpClient::HttpClient(QObject *parent) : QObject(parent) {
    m_manager = new QNetworkAccessManager(this);
    m_event_loop = new QEventLoop();
}

QJsonDocument *HttpClient::makeRequest(const QUrl &url) {
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager->get(request);

    connect(reply, &QNetworkReply::finished, m_event_loop, &QEventLoop::quit);
    m_event_loop->exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        reply->deleteLater();
        return new QJsonDocument(jsonDoc);
    } else {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return nullptr;
    }
}
