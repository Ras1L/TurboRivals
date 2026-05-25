#ifndef NETWORK_NETWORK_MANAGER_HPP
#define NETWORK_NETWORK_MANAGER_HPP

#include "Network/ENet.hpp"
#include "Network/IClient.hpp"
#include "Network/IServer.hpp"
#include "Network/NetworkRole.hpp"
#include "Network/NetworkStatus.hpp"

class NetworkManager {
public:
    void Init(NetworkRole role);
    void Deinit();

    void Connect(std::string ip);

    MsgQueue Update(float dt);
    
    void          SetStatus(NetworkStatus status);
    NetworkStatus GetStatus() const;

private:
    MsgQueue PollEvents();
    void     SendOutgoing(float dt);

private:
    IClient* client = nullptr;
    IServer* server = nullptr;

    ENet::Node node = nullptr;
};

#endif