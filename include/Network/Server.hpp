#ifndef NETWORK_SERVER_HPP
#define NETWORK_SERVER_HPP

#include "Core/PlayerConnectionDataManager.hpp"
#include "Network/ENet.hpp"
#include "Network/IServer.hpp"
#include "Network/NetworkMessage.hpp"
#include <unordered_map>

class Server final : public INetworkNode, public IServer {
public:
    void Init() override;
    void Destroy() override;

    void DisconnectClient(uint8_t id);

    void SendToClient(const NetworkMessage& msg, uint8_t id, float dt) override;
    void SendBroadcast(const NetworkMessage& msg, float dt)            override;

    MsgQueue PollEvents() override;

private:
    void   OnConnect(ENetPeer* peer) override;
    void   OnDisconnect(ENetPeer* peer) override;
    NetMsg OnReceive(ENetPeer* peer, ENetPacket* packet) override;

private:
    ENet::Addr address;
    ENet::Host server;
    std::unordered_map<ENetPeer*, SessionPlayerConnection> clients; // не оборачиваю в std::unique_ptr, это не вектор с переаллокациями

    PlayerConnectionDataManager connection_data_manager;
    float accum = 0.f;
};

#endif