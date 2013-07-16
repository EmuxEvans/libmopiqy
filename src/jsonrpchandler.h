#ifndef JSONRPCHANDLER_H
#define JSONRPCHANDLER_H

#include <QObject>
#include <QMap>
#include <QJsonObject>

#include "include/controllerinterface.h"

namespace Mopidy {
    namespace Internal {

        class JsonWebSocket;

        /*
         * Class to handle message sending/receiving for the different controllers
         */
        class JsonRpcHandler : public QObject
        {
            Q_OBJECT

        public:
            JsonRpcHandler(JsonWebSocket *socket, QObject *parent = 0);
            ~JsonRpcHandler();

            int sendMessage(Mopidy::Core::ControllerInterface *ci, const QJsonObject &msg, bool notification = false);

        private slots:
            void onResponse(const int &id, const QJsonValue &v);
            void onSocketDisconnected();

        private:
            QMap<int, Mopidy::Core::ControllerInterface*> m_mapMsg;
            JsonWebSocket *m_socket;
        };
    }
}

#endif //JSONRPCHANDLER_H
