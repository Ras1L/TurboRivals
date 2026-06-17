#ifndef NETWORK_ISERVER_HPP
#define NETWORK_ISERVER_HPP

#include "Network/NetworkMessage.hpp"

class IServer {
public:
    virtual void SendToClient(const NetworkMessage& msg, id_type id, float dt) = 0;
    virtual void SendBroadcast(const NetworkMessage& msg, float dt)            = 0;

    virtual ~IServer() = default;
};

#endif