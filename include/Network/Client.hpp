#ifndef NETWORK_CLIENT_HPP
#define NETWORK_CLIENT_HPP

#include "Network/NetworkManager.hpp"
#include "enet/enet.h"

class Client final : public INetworkListener {
public:
    void Init();
    void Destroy();

    void ConnectToServer(ENetAddress* address);
    void DisconnectFromServer();

    void OnConnect(ENetPeer* peer) override;
    void OnDisconnect(ENetPeer* peer) override;
    void OnReceive(ENetPeer* peer, ENetPacket* packet) override;

    void SendToServer(float dt);

private:
    Host client = nullptr;
    Peer server = nullptr; // сервер к которому подключаемся, для нас он пир

    float accum = 0.f; // переодическая отправка вне зависимости от FPS
};

#endif