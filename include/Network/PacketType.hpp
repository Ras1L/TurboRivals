#ifndef NETWORK_PACKET_TYPE_HPP
#define NETWORK_PACKET_TYPE_HPP

#include <cstdint>

enum class PacketType : uint8_t
{
    ClientInput,
    PlayerTransforms,

    ClientConfig,
    ServerGameConfig,
};

#endif