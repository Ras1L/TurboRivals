#ifndef NETWORK_MESSAGE_PROCESSOR_HPP
#define NETWORK_MESSAGE_PROCESSOR_HPP

#include "Core/Session.hpp"
#include "Network/NetworkMessage.hpp"
#include "Network/PacketType.hpp"
#include <enet/enet.h>

class MessageProcessor {
public:
    static SessionState        ApplyChanges(SessionState& session, MsgQueue& queue);
    static SessionStateRuntime ApplyChanges(SessionStateRuntime& session, MsgQueue& queue);

    static NetMsg         Serialize(ENetPacket* packet);
    static NetworkMessage Serialize(const PacketVariant& packet);

    static PacketVariant  Deserialize(const NetworkMessage& msg, bool);
};

#endif