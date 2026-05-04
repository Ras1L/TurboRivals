#ifndef NETWORK_NETWORK_STATUS_HPP
#define NETWORK_NETWORK_STATUS_HPP

#include <cstdint>

enum class NetworkStatus : uint8_t 
{
    OFFLINE,
    CLIENT,
    SERVER
};

#endif