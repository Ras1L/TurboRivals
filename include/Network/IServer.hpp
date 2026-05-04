#ifndef NETWORK_ISERVER_HPP
#define NETWORK_ISERVER_HPP

#include <cstdint>

class IServer {
public:
    virtual void SendToClient(uint8_t id, float dt) = 0;
    virtual void SendToClients(float dt) = 0;
    virtual void SendBroadcast(float dt) = 0;
};

#endif