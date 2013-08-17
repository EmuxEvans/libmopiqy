#include "qwebsocketclient.h"
#include "websocketutility.h"

#include <QUrl>
#include <QDebug>
#include <QDateTime>

using namespace Mopidy::Internal;

QWebSocketClient::QWebSocketClient(QObject *parent) : QObject(parent)
{
    qsrand(QDateTime::currentDateTime().toTime_t());

    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onTcpError(QAbstractSocket::SocketError)));
    connect(m_tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onTcpStateChanged(QAbstractSocket::SocketState)));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(onTcpReadyRead()));
}

QWebSocketClient::~QWebSocketClient()
{
    disconnectFromHost();
    m_tcpSocket->deleteLater();
}

bool QWebSocketClient::connectToHost(const QString &host, const quint16 &port, const QString &path)
{
    // Close before trying to connect to another one
    disconnectFromHost();

    // parse URL to initiate tcp connection
    QUrl url = QUrl::fromUserInput(host);
    if((url.port() == -1) && (url.port() != port) && (port != 80)) url.setPort(port);
    if(!path.isEmpty()) url.setPath(path);

    if(url.scheme() == "ws") url.setScheme("http");
    else if(url.scheme() == "wss") url.setScheme("https");

    if(!url.isValid()) return false;

    m_currentPort = url.port();
    m_currentHost = url.host();
    m_currentPath = url.path();

    m_tcpSocket->connectToHost(url.host(), url.port());
    return true;
}

bool QWebSocketClient::isConnected() const
{
    return m_tcpSocket->isOpen();
}

bool QWebSocketClient::disconnectFromHost()
{
    if(m_tcpSocket->state() == QTcpSocket::ConnectedState)
    {
        if(m_wsState == QAbstractSocket::ConnectedState)
        {
            QByteArray closeFrame = WebSocketUtility::createFrameHeader(
                        WebSocketUtility::Op_Close,
                        0, true, WebSocketUtility::createRandomKey(4, false));

            m_tcpSocket->write(closeFrame);
            m_wsState = QAbstractSocket::ClosingState;
        }
    }

    return true;
}

void QWebSocketClient::ping()
{
    if(m_wsState == QAbstractSocket::ConnectedState)
    {
        QByteArray k = WebSocketUtility::createRandomKey(4, false);
        QByteArray pingFrame = WebSocketUtility::createFrameHeader(WebSocketUtility::Op_Ping, 0, true, k);
        m_tcpSocket->write(pingFrame);
    }
}

void QWebSocketClient::writeTextMessage(const QString &message)
{
    writeMessage(message.toUtf8(), true);
}

void QWebSocketClient::writeBinaryMessage(const QByteArray &message)
{
    writeMessage(message, false);
}

void QWebSocketClient::onTcpError(QAbstractSocket::SocketError se)
{
    emit error(se, m_tcpSocket->errorString());
}

void QWebSocketClient::onTcpStateChanged(QAbstractSocket::SocketState state)
{
    switch(state)
    {
    case QAbstractSocket::ConnectedState:
        m_wsState = QAbstractSocket::ConnectingState;
        m_currentSessionHSKey = WebSocketUtility::createRandomKey(16, true);
        m_tcpSocket->write(WebSocketUtility::createConnectedHandshake(
                               m_currentPath,
                               m_currentHost + ":" + QString::number(m_currentPort),
                               m_currentSessionHSKey));
        break;

    case QAbstractSocket::ClosingState:
        if(m_wsState != QAbstractSocket::ClosingState)
        {

        }
        break;

    case QAbstractSocket::UnconnectedState:
        if(m_wsState == QAbstractSocket::ClosingState)
        {
           m_wsState = QAbstractSocket::UnconnectedState;
           m_currentHost = "";
           m_currentPath = "";
           m_currentPort = 0;
           m_currentSessionHSKey.clear();

           emit disconnected();
        }
        break;


    default:
        break;
    }
}

void QWebSocketClient::onTcpReadyRead()
{
    switch(m_wsState)
    {
    case QAbstractSocket::ConnectingState:
        processWsConnecting(m_tcpSocket->readAll());
        break;

    case QAbstractSocket::ConnectedState:
        processWsRead(m_tcpSocket->readAll());
        break;

    case QAbstractSocket::ClosingState:
        // log reason ?
        break;

    default:
        break;
    }

}

void QWebSocketClient::processWsConnecting(const QByteArray &tcpData)
{
    bool failConnection = false;
    int statusCode;
    QMap<QString, QString> httpContent = WebSocketUtility::parseHttpHeader(tcpData, statusCode);

    switch(statusCode)
    {
    case 101: // Switching protocol
        if(!httpContent.contains("upgrade"))
        {
            failConnection = true;
        }
        else if(!httpContent.contains("connection"))
        {
            failConnection = true;
        }
        else if(QString::compare("upgrade", httpContent.value("connection"), Qt::CaseInsensitive) != 0)
        {
            failConnection = true;
        }
        else if(!httpContent.contains("sec-websocket-accept"))
        {
            failConnection = true;
        }
        else if(!WebSocketUtility::checkWsAcceptKey(
                    httpContent.value("sec-websocket-accept").toLatin1(),
                    m_currentSessionHSKey))
        {
            failConnection = true;
        }

        // TODO: check extensions
        // TODO: check sub-protocols

        if(failConnection)
        {
            m_wsState = QAbstractSocket::UnconnectedState;
            m_tcpSocket->close();
            emit error(1, "Connection failed");
        }
        else
        {
            m_wsState = QAbstractSocket::ConnectedState;
            emit connected();
        }
        break;

    default:
        emit error(statusCode, "unmanaged code");
        break;
    }
}

void QWebSocketClient::processWsRead(const QByteArray &tcpData)
{
    bool eof;
    quint64 payloadsize;
    WebSocketUtility::OpCode opcode;
    QByteArray mask;

    QByteArray ba = WebSocketUtility::extractFrameHeader(tcpData, opcode, payloadsize, eof, mask);

    switch(opcode)
    {
    case WebSocketUtility::Op_Pong:
        emit pong();
        break;

    case WebSocketUtility::Op_Ping:
        sendPong();
        break;

    case WebSocketUtility::Op_Close:
        emit disconnected();
        break;

    case WebSocketUtility::Op_Binary:
        emit binaryMessageReceived(ba);
        break;

    case WebSocketUtility::Op_Text:
        emit textMessageReceived(ba);
        break;

    default:
        break;
    }
}

void QWebSocketClient::writeMessage(const QByteArray &data, bool sendAsText)
{
    QList<QByteArray> frames = WebSocketUtility::createFrames(data, sendAsText);
    foreach(QByteArray frame, frames)
    {
        m_tcpSocket->write(frame);
        m_tcpSocket->waitForBytesWritten();
    }
}


void QWebSocketClient::sendPong()
{
    if(m_wsState == QAbstractSocket::ConnectedState)
    {
        QByteArray pingFrame = WebSocketUtility::createFrameHeader(WebSocketUtility::Op_Pong, 0, true);
        m_tcpSocket->write(pingFrame);
    }
}
