#ifndef NETWORK_SERVER_HPP
#define NETWORK_SERVER_HPP

#include "Network/NetworkManager.hpp"
#include "enet/enet.h"
#include <unordered_map>

class Server final : INetworkListener {
public:
    void Init();
    void Destroy();

    void DisconnectClient(uint8_t id);

    void SendToClient(uint8_t id, float dt);
    void SendToClients(float dt);
    void SendBroadcast(float dt);

    void Update();

private:
    void OnConnect(ENetPeer* peer) override;
    void OnDisconnect(ENetPeer* peer) override;
    void OnReceive(ENetPeer* peer, ENetPacket* packet) override;

private:
    Addr address;
    Host server;
    std::unordered_map<uint8_t, Peer> clients;

    uint8_t client_ids = 0;
    float accum          = 0.f;
};

#endif