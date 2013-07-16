#include "controllerinterface.h"

using namespace Mopidy::Core;

ControllerInterface::ControllerInterface(Mopidy::Internal::JsonRpcHandler *jrHandler)
{
    m_jrHandler = jrHandler;
}
