#ifndef NETWORK_CLIENT_HPP
#define NETWORK_CLIENT_HPP

#include "Network/ENet.hpp"
#include "Network/IClient.hpp"
#include "Network/NetworkMessage.hpp"
#include "enet/enet.h"
#include "enet/types.h"

class Client final : public INetworkNode, public IClient {
public:
    void Init() override;
    void Destroy() override;

    void ConnectToServer(std::string ip) override;
    void DisconnectFromServer();

    void   SendToServer(float dt) override;
    NetMsg Receive(enet_uint32 ms) override; // нужно чтобы клиент до начала игры мог получить данные о сессии, схож с Update 

    void Update() override;

private:
    void   OnConnect(ENetPeer* peer) override;
    void   OnDisconnect(ENetPeer* peer) override;
    NetMsg OnReceive(ENetPeer* peer, ENetPacket* packet) override;

private:
    ENet::Addr server_addr;
    ENet::Host client = nullptr;
    ENet::Peer server = nullptr; // сервер к которому подключаемся, для нас он пир

    float accum = 0.f; // переодическая отправка вне зависимости от FPS
};

#endif