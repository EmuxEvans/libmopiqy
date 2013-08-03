#include "testjsonrpchandler.h"
#include "../src/jsonrpchandler.h"
#include "../src/jsonwebsocket.h"

void TestJsonRpcHandler::sendMessageSuccess()
{
    Mopidy::Internal::JsonWebSocket jws;
    Mopidy::Internal::JsonRpcHandler jrh(&jws, this);
    QVERIFY(jrh.sendMessage(0, QJsonObject(), false) > 0);
    QVERIFY(jrh.sendMessage(0, QJsonObject(), true) == 0);
}

void TestJsonRpcHandler::noSocketSendMessage()
{
    Mopidy::Internal::JsonRpcHandler jrh(0, this);
    QVERIFY(jrh.sendMessage(0, QJsonObject()) == -1);
}
