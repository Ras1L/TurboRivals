#ifndef NETWORK_SERVER_HPP
#define NETWORK_SERVER_HPP

#include "Network/ENet.hpp"
#include "Network/IServer.hpp"
#include "enet/enet.h"
#include <unordered_map>

class Server final : public INetworkNode, public IServer {
public:
    void Init() override;
    void Destroy() override;

    void DisconnectClient(uint8_t id);

    void SendToClient(uint8_t id, float dt) override;
    void SendToClients(float dt) override;
    void SendBroadcast(float dt) override;

    void Update() override;

private:
    void OnConnect(ENetPeer* peer) override;
    void OnDisconnect(ENetPeer* peer) override;
    void OnReceive(ENetPeer* peer, ENetPacket* packet) override;

private:
    ENet::Addr address;
    ENet::Host server;
    std::unordered_map<uint8_t, ENet::Peer> clients;

    uint8_t client_ids = 0;
    float accum        = 0.f;
};

#endif