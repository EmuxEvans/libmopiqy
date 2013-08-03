#include "testmopidyparser.h"

void TestMopidyParser::rpcEncode()
{
    QString str = "encode";
    QVERIFY(str.toUpper() == "ENCODE");
}
