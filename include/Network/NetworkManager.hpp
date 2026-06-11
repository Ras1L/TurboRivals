#ifndef NETWORK_NETWORK_MANAGER_HPP
#define NETWORK_NETWORK_MANAGER_HPP

#include "Network/ENet.hpp"
#include "Network/IClient.hpp"
#include "Network/IServer.hpp"
#include "Network/NetworkMessage.hpp"
#include "Network/NetworkRole.hpp"
#include "Network/NetworkStatus.hpp"

class NetworkManager {
public:
    NetworkManager() = default;
    NetworkManager(const NetworkManager&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;

    void Init(NetworkRole role);
    void Deinit();

    bool Connect(std::string ip);

    MsgQueue Update(const NetworkMessage& msg, float dt);
    
    void          SetStatus(NetworkStatus status);
    NetworkStatus GetStatus() const;
    NetworkRole   GetRole() const;

private:
    MsgQueue PollEvents();
    void     SendOutgoing(const NetworkMessage& msg, float dt);

private:
    IClient* client = nullptr;
    IServer* server = nullptr;

    ENet::Node  node = nullptr;
    NetworkRole role;
};

#endif