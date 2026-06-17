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

    void DisconnectClient(id_type id);

    void SendToClient(const NetworkMessage& msg, id_type id, float dt) override;
    void SendToClient(const NetworkMessage& msg, ENetPeer* peer, float dt);
    void SendBroadcast(const NetworkMessage& msg, float dt)            override;

    MsgQueue PollEvents() override;

private:
    void   OnConnect(ENetPeer* peer) override;
    void   OnDisconnect(ENetPeer* peer) override;
    NetMsg OnReceive(ENetPeer* peer, ENetPacket* packet) override;

private:
    float accum = 0.f;
    PlayerConnectionDataManager connection_data_manager;

    ENet::Addr address;
    ENet::Host server;
    std::unordered_map<ENetPeer*, SessionPlayerConnection> clients; // не оборачиваю в std::unique_ptr, это не вектор с переаллокациями
    std::unordered_map<uint8_t, ENetPeer*> fast_search; // второй std::unordered_map<id, ENetPeer> для быстрого выполнения
};

#endif