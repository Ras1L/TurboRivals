#ifndef NETWORK_NETWORK_MESSAGE_HPP
#define NETWORK_NETWORK_MESSAGE_HPP

#include "Core/EasyBytes.hpp"
#include "PacketType.hpp"

#include <enet/enet.h>
#include <optional>
#include <queue>

struct NetworkMessage {
    ENetPeer*  peer;
    PacketType type;
    EasyBytes  payload;
};

using NetMsg   = std::optional<NetworkMessage>;
using MsgQueue = std::queue<NetworkMessage>;

#endif