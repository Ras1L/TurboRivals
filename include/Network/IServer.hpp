#ifndef NETWORK_ISERVER_HPP
#define NETWORK_ISERVER_HPP

#include "Network/NetworkMessage.hpp"
#include <cstdint>

class IServer {
public:
    virtual void SendToClient(const NetworkMessage& msg, uint8_t id, float dt) = 0;
    virtual void SendBroadcast(const NetworkMessage& msg, float dt)            = 0;
};

#endif