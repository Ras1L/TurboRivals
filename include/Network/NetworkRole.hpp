#ifndef NETWORK_NETWORK_ROLE_HPP
#define NETWORK_NETWORK_ROLE_HPP

#include <cstdint>

enum class NetworkRole : uint8_t 
{
    OFFLINE,
    CLIENT,
    SERVER
};

#endif