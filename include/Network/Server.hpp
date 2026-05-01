#ifndef NETWORK_SERVER_HPP
#define NETWORK_SERVER_HPP

#include "Network/INetworkListener.hpp"
#include "Network/NetworkManager.hpp"
#include "enet/enet.h"
#include <vector>

class Server final : public INetworkListener
{
public:
    void Init();
    void Destroy();

    void DisconnectClient(ENetPeer* peer);

    void OnConnect(ENetPeer* peer) override;
    void OnDisconnect(ENetPeer* peer) override;
    void OnReceive(ENetPeer* peer, ENetPacket* packet) override;

    void SendToClient(ENetPeer* peer, float dt);
    void SendBroadcast(float dt);

private:
    ENetAddress       address;
    Host              server;
    std::vector<Peer> clients;

    float accum;
};

#endif