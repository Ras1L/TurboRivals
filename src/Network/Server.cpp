#include "Network/Server.hpp"
#include "Network/NetworkManager.hpp"
#include "Network/PacketType.hpp"
#include "enet/enet.h"
#include <algorithm>
#include <memory>
#include <pstl/glue_algorithm_defs.h>

void Server::Init()
{
    server = NetworkManager::CreateServer(&address);
}

void Server::Destroy()
{
    NetworkManager::DestroyHost(server.get());
}

void Server::DisconnectClient(ENetPeer* peer)
{
    auto it = std::find_if(clients.cbegin(), clients.cend(), 
    [peer](auto& p) {
        return p.get() == peer;
    });
    if (it != clients.cend()) {
        NetworkManager::DisconnectPeer(server.get(), it->get());
    }
}

void Server::OnConnect(ENetPeer* peer)
{
    // peer -> data тоже надо, но пока хз что там должно быть
    Peer client(peer);
    clients.push_back(std::move(client));
}

void Server::OnDisconnect(ENetPeer* peer)
{
    auto it = std::find_if(clients.cbegin(), clients.cend(), 
    [peer](auto& p) {
        return p.get() == peer;
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

void Server::SendToClient(ENetPeer* peer, float dt) // это избранные данные клиентам передавать
{
    accum += dt;
    if (accum >= tickRate) {
        NetworkManager::SendPacketToPeer(peer);
    }
    accum -= tickRate;
}

void Server::SendBroadcast(float dt) // это для всех передавать одно и то же
{
    accum += dt;
    if (accum >= tickRate) {
        NetworkManager::SendFromHostBroadcast(server.get());
    }
    accum -= tickRate;
}