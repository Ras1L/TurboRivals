#ifndef NETWORK_NETWORK_MANAGER_HPP
#define NETWORK_NETWORK_MANAGER_HPP

#include "Network/ENet.hpp"
#include "Network/IClient.hpp"
#include "Network/IServer.hpp"
#include "Network/NetworkStatus.hpp"

class NetworkManager {
public:
    void Init(NetworkStatus status);
    void Deinit();

    void Update(float dt);

private:
    ENet::Node node = nullptr;
    IClient* client = nullptr;
    IServer* server = nullptr;
};

#endif