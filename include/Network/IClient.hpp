#ifndef NETWORK_ICLIENT_HPP
#define NETWORK_ICLIENT_HPP

#include "Network/NetworkMessage.hpp"
#include <string>

class IClient {
public:
    virtual void SendToServer(const NetworkMessage& msg, float dt) = 0;
    virtual bool ConnectToServer(std::string ip)                   = 0;

    virtual ~IClient() = default;

    bool is_connected = false;
};

#endif