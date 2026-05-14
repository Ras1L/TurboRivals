#ifndef NETWORK_NETWORK_MANAGER_HPP
#define NETWORK_NETWORK_MANAGER_HPP

#include "Network/NetworkMessage.hpp"
#include "Network/ENet.hpp"
#include "Network/IClient.hpp"
#include "Network/IServer.hpp"
#include "Network/NetworkStatus.hpp"

class NetworkManager {
public:
    void Init(NetworkStatus status);
    void Deinit();

    void Connect(std::string ip);
    void Update(float dt);

    NetMsg WaitForStart(float seconds);

private:
    ENet::Node node = nullptr;
    IClient* client = nullptr;
    IServer* server = nullptr;
};

#endif