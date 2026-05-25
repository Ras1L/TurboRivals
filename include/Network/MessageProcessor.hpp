#ifndef NETWORK_MESSAGE_PROCESSOR_HPP
#define NETWORK_MESSAGE_PROCESSOR_HPP

#include "Core/Session.hpp"
#include "Network/NetworkMessage.hpp"
#include <enet/enet.h>

class MessageProcessor {
public:
    static SessionState ApplyChanges(SessionState& session, MsgQueue& queue);
    static Session      Deserialize(const NetworkMessage& msg);
    static NetMsg       Serialize(ENetPacket* packet);
};

#endif