#include "Network/Server.hpp"
#include "Network/ENet.hpp"
#include "Network/MessageProcessor.hpp"
#include "Network/NetworkMessage.hpp"

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

void Server::OnConnect(ENetPeer* peer) // Здесь сервер не меняет состояние он почти всегда просто IDLE
{
    auto current_id = client_ids++;
    clients.insert({current_id, ENet::Peer(peer)});
    peer -> data = reinterpret_cast<void*>(static_cast<uintptr_t>(current_id));
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

NetMsg Server::OnReceive(ENetPeer* peer, ENetPacket* packet) // а вот пакеты разные приходят
{
    auto id = static_cast<uint8_t*>(peer -> data)[0]; // что за клиент пришел
    if (clients.contains(id))
    {
        return MessageProcessor::Serialize(packet);
    }
    return std::nullopt;
}

void Server::SendToClient(const NetworkMessage& msg, uint8_t id, float dt) // это избранные данные клиентам передавать
{
    EasyBytes bytes;
    bytes.Write(msg.type);
    bytes.Write(msg.payload.Data(), msg.payload.Size());

    auto peer = clients.find(id) -> second.get();
    accum += dt;
    if (accum >= tickRate) {
        ENet::SendPacketToPeer(peer, bytes.Data(), bytes.Size());
    }
    accum -= tickRate;
}

void Server::SendToClients(const NetworkMessage& msg, float dt)
{
    EasyBytes bytes;
    bytes.Write(msg.type);
    bytes.Write(msg.payload.Data(), msg.payload.Size());

    accum += dt;
    if (accum >= tickRate) {
        std::for_each(clients.cbegin(), clients.cend(), 
        [&bytes](auto& p){
            ENet::SendPacketToPeer(p.second.get(), bytes.Data(), bytes.Size());
        });
    }
    accum -= tickRate;
}

void Server::SendBroadcast(const NetworkMessage& msg, float dt) // это для всех передавать одно и то же
{
    EasyBytes bytes;
    bytes.Write(msg.type);
    bytes.Write(msg.payload.Data(), msg.payload.Size());

    accum += dt;
    if (accum >= tickRate) {
        ENet::SendFromHostBroadcast(server.get(), bytes.Data(), bytes.Size());
    }
    accum -= tickRate;
}

MsgQueue Server::PollEvents()
{
    return ENet::PollEvents(server.get(), *this, 0);
}