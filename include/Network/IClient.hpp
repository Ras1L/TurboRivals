#ifndef NETWORK_ICLIENT_HPP
#define NETWORK_ICLIENT_HPP

#include "Network/NetworkMessage.hpp"
#include "enet/types.h"
#include <string>

class IClient {
public:
    virtual void   SendToServer(float dt)          = 0;
    virtual void   ConnectToServer(std::string ip) = 0;
    virtual NetMsg Receive(enet_uint32 ms)         = 0; 
};

#endif