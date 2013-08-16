#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

#include <QMap>
#include <QJsonValue>

namespace Mopidy {

    namespace Internal {
        class JsonRpcHandler;
    }

    namespace Core {
        /*
         * Abstract class for each Controller class
         * - process json response
         * - keep json-rpc handler
         * - keep map with message sended waiting for response
         */
        class ControllerInterface
        {
        public:
            ControllerInterface(Mopidy::Internal::JsonRpcHandler *jrHandler);

        protected:
            friend class Mopidy::Internal::JsonRpcHandler;
            virtual void processJsonResponse(const int &id, const QJsonValue &jo) = 0;

        protected:
            Mopidy::Internal::JsonRpcHandler *m_jrHandler;

            // map to store id / request type per controller
            QMap<int, int> m_idQuery;
        };
    }
}

#endif //CONTROLLERINTERFACE_H
