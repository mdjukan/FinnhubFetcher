#ifndef TDWEBSOCKETCLIENT_H
#define TDWEBSOCKETCLIENT_H

#include <QWebSocket>
#include <QWebSocketServer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class TDWebSocketClient : public QObject {
    Q_OBJECT

public:
    TDWebSocketClient(const QString &apiKey, QObject *parent = nullptr)
        : QObject(parent), m_apiKey(apiKey), m_webSocket(new QWebSocket()) {

        connect(m_webSocket, &QWebSocket::errorOccurred, this, &TDWebSocketClient::onErrorOccurred);
        connect(m_webSocket, &QWebSocket::connected, this, &TDWebSocketClient::onConnected);
        connect(m_webSocket, &QWebSocket::disconnected, this, &TDWebSocketClient::onDisconnected);
        connect(m_webSocket, &QWebSocket::textMessageReceived, this, &TDWebSocketClient::onTextMessageReceived);
    }

    void connectToServer() {
        m_webSocket->open(QUrl("wss://ws.twelvedata.com/v1/quotes/price?apikey=d4b37649faf1431e99784e09402a3c48"));
    }

    void subscribe(const QString &symbol) {
        qDebug() << "subsrcibe call";
        // Send subscription message to the server
        QJsonObject json;
        json["action"] = "subscribe";
        QJsonObject params;
        params["symbols"] = "EUR/USD";
        json["params"] = params;

        QJsonDocument doc(json);
        qDebug() << doc.toJson();
        m_webSocket->sendTextMessage(doc.toJson());
    }

    void closeConnection() {
        if (m_webSocket->state() == QAbstractSocket::ConnectedState) {
            m_webSocket->close(); // Gracefully close the connection
            qDebug() << "WebSocket connection closed.";
        } else {
            qDebug() << "WebSocket is not connected.";
        }
    }

private slots:

    void onErrorOccurred(QAbstractSocket::SocketError error) {
        switch (error) {
        case QAbstractSocket::ConnectionRefusedError:
            qDebug() << "Connection refused: The server is not available.";
            break;
        case QAbstractSocket::RemoteHostClosedError:
            qDebug() << "Remote host closed the connection.";
            break;
        case QAbstractSocket::HostNotFoundError:
            qDebug() << "Host not found: The URL may be incorrect.";
            break;
        case QAbstractSocket::SocketAccessError:
            qDebug() << "Socket access error: Check your permissions.";
            break;
        case QAbstractSocket::SocketResourceError:
            qDebug() << "Socket resource error: Resources are exhausted.";
            break;
        case QAbstractSocket::NetworkError:
            qDebug() << "Network error: Check your network connection.";
            break;
        case QAbstractSocket::UnknownSocketError:
        default:
            qDebug() << "An unknown error occurred:" << m_webSocket->errorString();
            break;
        }
    }
    void onConnected() {
        qDebug() << "WebSocket connected.";
    }

    void onDisconnected() {
        qDebug() << "WebSocket disconnected.";
    }

    void onTextMessageReceived(const QString &message) {
        qDebug() << "Message received:" << message;
        // Handle the incoming message
        QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
        qDebug() << doc.toJson();
    }

private:
    QString m_apiKey;
    QWebSocket *m_webSocket;
};

#endif // TDWEBSOCKETCLIENT_H
