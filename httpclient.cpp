#include "httpclient.h"

HttpClient::HttpClient(QObject *parent) : QObject(parent) {
    m_manager = new QNetworkAccessManager(this);
}

void HttpClient::makeRequest(const QUrl &url) {
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleResponse(reply);
    });
}

void HttpClient::handleResponse(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    parseJson(responseData);
    reply->deleteLater();
}

void HttpClient::parseJson(const QByteArray &data) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to create JSON doc.";
        return;
    }

    if (jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();
        qDebug() << "Parsed JSON object:" << jsonObj;
    } else if (jsonDoc.isArray()) {
        QJsonArray jsonArray = jsonDoc.array();
        qDebug() << "Parsed JSON array:" << jsonArray;
    }
}
