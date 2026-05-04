#ifndef NETWORK_ICLIENT_HPP
#define NETWORK_ICLIENT_HPP

class IClient {
public:
    virtual void SendToServer(float dt) = 0;
};

#endif