#ifndef WEBSOCKETUTILITY_H
#define WEBSOCKETUTILITY_H

#include <QString>
#include <QMap>

namespace Mopidy {
    namespace Internal {
        class WebSocketUtility
        {
        public:

            enum OpCode {
                Op_Continue = 0x0,
                Op_Text     = 0x1,
                Op_Binary   = 0x2,
                Op_Close    = 0x8,
                Op_Ping     = 0x9,
                Op_Pong     = 0xA
            };

            static QByteArray createConnectedHandshake(const QString &path, const QString &host, const QByteArray &key);
            static QByteArray createRandomKey(const int &keySize, bool encode64);
            static QMap<QString, QString> parseHttpHeader(const QByteArray &, int &statusCode);
            static bool checkWsAcceptKey(const QByteArray &wsKey, const QByteArray &sessionKey);
            static QByteArray createFrameHeader(const OpCode &opcode, const quint64 &payloadSize = 0, const bool &endOfFrame = true, const QByteArray &maskKey = QByteArray());
            static QList<QByteArray> createFrames(const QByteArray &message, bool sendAsText);

            // returns payload data only
            static QByteArray extractFrameHeader(const QByteArray &data, OpCode &opcode, quint64 &payloadLength, bool &endOfFrame, QByteArray &maskKey);

            static QByteArray applyMask(const QByteArray &data, const QByteArray &mask);
        };
    }
}

#endif //WEBSOCKETUTILITY_H
