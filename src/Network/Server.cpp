#include "Network/Server.hpp"
#include "Network/ENet.hpp"
#include "Network/PacketType.hpp"

#include <algorithm>

void Server::Init()
{
    server = ENet::CreateServer(&address);
}

void Server::Destroy()
{
    ENet::DestroyHost(server.get());
}

void Server::DisconnectClient(uint8_t id)
{
    auto it = clients.find(id);
    if (it != clients.cend()) {
        ENet::DisconnectPeer(server.get(), it -> second.get());
    }
}

void Server::OnConnect(ENetPeer* peer)
{
    // peer -> data тоже надо, но пока хз что там должно быть
    while (!clients.insert({client_ids++, ENet::Peer(peer)}).second) {}
}

void Server::OnDisconnect(ENetPeer* peer)
{
    auto it = std::find_if(clients.cbegin(), clients.cend(), 
    [peer](auto& p) {
        return p.second.get() == peer;
    });
    if (it != clients.cend()) {
        clients.erase(it);
    }
}

void Server::OnReceive(ENetPeer* peer, ENetPacket* packet) // а вот пакеты разные приходят
{
    (void) peer;
    PacketType pt = static_cast<PacketType>(packet -> data[0]);
    switch (pt) 
    {
        case PacketType::ClientInput:
            // TODO
            return;

        default:
            break;
    }
}

void Server::SendToClient(uint8_t id, float dt) // это избранные данные клиентам передавать
{
    auto peer = clients.find(id) -> second.get();
    accum += dt;
    if (accum >= tickRate) {
        ENet::SendPacketToPeer(peer);
    }
    accum -= tickRate;
}

void Server::SendToClients(float dt)
{
    accum += dt;
    if (accum >= tickRate) {
        std::for_each(clients.cbegin(), clients.cend(), 
        [](auto& p){
            ENet::SendPacketToPeer(p.second.get());
        });
    }
    accum -= tickRate;
}

void Server::SendBroadcast(float dt) // это для всех передавать одно и то же
{
    accum += dt;
    if (accum >= tickRate) {
        ENet::SendFromHostBroadcast(server.get());
    }
    accum -= tickRate;
}

void Server::Update()
{
    ENet::PollEvents(server.get(), *this);
}