#ifndef NETWORK_NETWORK_MESSAGE_HPP
#define NETWORK_NETWORK_MESSAGE_HPP

#include "PacketType.hpp"
#include "enet/types.h"
#include <optional>
#include <vector>

using ByteBuffer = std::vector<enet_uint8>;

struct NetworkMessage {
    PacketType type;
    ByteBuffer payload;
};

using NetMsg = std::optional<NetworkMessage>;

#endif