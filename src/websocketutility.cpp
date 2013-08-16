#include "websocketutility.h"

#include <QTextStream>
#include <QCryptographicHash>
#include <QtEndian>

#define CRLF "\r\n"
#define MAX_TX_FRAMESIZE 1536

using namespace Mopidy::Internal;

QByteArray WebSocketUtility::createConnectedHandshake(const QString &path, const QString &host, const QByteArray &key)
{
    QString hs;
    QTextStream ts(&hs);

    if(path.startsWith("/"))
        ts << "GET " << path << " HTTP/1.1" << CRLF;
    else
        ts << "GET /" << path << " HTTP/1.1" << CRLF;

    ts << "Host: " << host << CRLF;
    ts << "Upgrade: websocket" << CRLF;
    ts << "Connection: Upgrade" << CRLF;
    ts << "Sec-WebSocket-Key: " << key << CRLF;
    ts << "Sec-WebSocket-Version: 13" << CRLF;
    ts << CRLF;

    return hs.toLatin1();
}

QByteArray WebSocketUtility::createRandomKey(const int &keySize, bool encode64)
{
    QByteArray key;
    int i = keySize;

    while(i--)
    {
        key.append(qrand() % 0xff);
    }

    if(encode64)
        return key.toBase64();
    else
        return key;
}

QMap<QString, QString> WebSocketUtility::parseHttpHeader(const QByteArray &data, int &statusCode)
{
    if(data.startsWith("HTTP"))
    {
        QMap<QString, QString> headers;


        // extract status code
        QList<QByteArray> hdrResult = data.mid(0, data.indexOf('\n')).trimmed().split(' ');
        if(hdrResult.size() > 3)
        {
            statusCode = QString(hdrResult.at(1)).toInt();
        }

        // extract content
        QByteArray hdrContent = data.mid(data.indexOf('\n') + 1).trimmed();

        // split content
        foreach(QByteArray line, hdrContent.split('\n'))
        {
            int colon = line.indexOf(':');
            QByteArray headerName = line.left(colon).trimmed().toLower();
            QByteArray headerValue = line.mid(colon + 1).trimmed();

            headers.insertMulti(headerName, headerValue);
        }

        return headers;
    }
    else
    {
        statusCode = 404;
        return QMap<QString, QString>();
    }
}

bool WebSocketUtility::checkWsAcceptKey(const QByteArray &wsKey, const QByteArray &sessionKey)
{
    QByteArray keyToCheck;
    keyToCheck.append(sessionKey);
    keyToCheck.append("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
    QByteArray hash = QCryptographicHash::hash(keyToCheck, QCryptographicHash::Sha1);

    return (hash.toBase64() == wsKey);
}

QByteArray WebSocketUtility::createFrameHeader(const OpCode &opcode, const quint64 &payloadLength, const bool &endOfFrame, const QByteArray &maskKey)
{
    QByteArray baFH;

    char byte = 0x00;

    // FIN, RSVx, Opcode
    if(endOfFrame) byte |= 0x80;
    byte |= opcode;
    baFH.append(byte);

    byte = 0x00;
    // mask, payload size
    if(maskKey.size() == 4) byte |= 0x80;
    if(payloadLength < 126)
    {
        byte |= payloadLength;
        baFH.append(byte);
    }
    // Extended payloadLength
    else
    {
        QByteArray extPS;
        // 2 bytes
        if (payloadLength <= 0xFFFF)
        {
            byte = (byte | 126);
            extPS.append((payloadLength >> 1*8) & 0xFF);
            extPS.append((payloadLength >> 0*8) & 0xFF);
        }
        // 8 bytes
        else if (payloadLength <= 0x7FFFFFFF)
        {
            byte = (byte | 127);
            extPS.append((payloadLength >> 7*8) & 0xFF);
            extPS.append((payloadLength >> 6*8) & 0xFF);
            extPS.append((payloadLength >> 5*8) & 0xFF);
            extPS.append((payloadLength >> 4*8) & 0xFF);
            extPS.append((payloadLength >> 3*8) & 0xFF);
            extPS.append((payloadLength >> 2*8) & 0xFF);
            extPS.append((payloadLength >> 1*8) & 0xFF);
            extPS.append((payloadLength >> 0*8) & 0xFF);
        }
        baFH.append(byte);
        baFH.append(extPS);
    }

    // mask
    if(maskKey.size() == 4) baFH.append(maskKey);

    return baFH;
}

QList<QByteArray> WebSocketUtility::createFrames(const QByteArray &message, bool sendAsText)
{
    QList<QByteArray> frames;

    OpCode opcode;
    quint64 payloadLength;
    QByteArray mask;

//    QByteArray msg = sendAsText ? QString::fromLatin1(message).toUtf8() : message;

    // split into pieces
    int nFrames = (message.size() / MAX_TX_FRAMESIZE) + 1;
    for(int i = 0; i < nFrames; ++i)
    {
        // get opcode
        if((nFrames > 1) && (i != 0)) opcode = Op_Continue;
        else opcode = sendAsText ? Op_Text : Op_Binary;

        // adjust size
        if(i == (nFrames - 1))
        {
            payloadLength = message.size() - (i * MAX_TX_FRAMESIZE);
        }

        // mask
        mask = createRandomKey(4, false);

        // create header
        QByteArray hdr  = createFrameHeader(opcode, payloadLength, (i == (nFrames - 1)), mask);

        // create masked data
        QByteArray data = applyMask(message.mid(i * MAX_TX_FRAMESIZE, payloadLength), mask);

        // merge and add
        hdr.append(data);
        frames << hdr;
    }

    return frames;
}

QByteArray WebSocketUtility::extractFrameHeader(const QByteArray &data, WebSocketUtility::OpCode &opcode, quint64 &payloadLength, bool &endOfFrame, QByteArray &maskKey)
{
    int bIndex = 0;

    // FIN, RSVx, Opcode
    endOfFrame = (data[bIndex] & 0x80) != 0;
    opcode = (WebSocketUtility::OpCode)(data[bIndex] & 0x0F);
    bIndex++;

    // mask, payload
    bool hasMask = (data[bIndex] & 0x80) != 0;
    payloadLength = (data[bIndex] & 0x7F);
    bIndex++;

    if(payloadLength == 126)
    {
        uchar pl[2];
        pl[0] = data[bIndex++];
        pl[1] = data[bIndex++];
        payloadLength = qFromBigEndian<quint16>(reinterpret_cast<const uchar *>(pl));
    }
    else if(payloadLength == 127)
    {
        uchar pl[8];
        for(int i = 0; i < 8; ++i) pl[i] = data[bIndex++];
        payloadLength = qFromBigEndian<quint64>(pl) & ~(1LL << 63);
    }

    if(hasMask)
    {
        maskKey = data.mid(bIndex, 4);
        bIndex += 4;
    }

    return data.mid(bIndex);
}


QByteArray WebSocketUtility::applyMask(const QByteArray &data, const QByteArray &mask)
{
    QByteArray result;
    result.reserve(data.size());

    for (int i = 0; i < data.size(); ++i)
        result[i] = (data[i] ^ mask[i % 4]);

    return result;
}
