#ifndef NETWORK_ICLIENT_HPP
#define NETWORK_ICLIENT_HPP

#include <string>

class IClient {
public:
    virtual void SendToServer(float dt)          = 0;
    virtual void ConnectToServer(std::string ip) = 0;
};

#endif