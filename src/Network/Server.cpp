#include "Network/Server.hpp"
#include "Core/Session.hpp"
#include "Network/ENet.hpp"
#include "Network/MessageProcessor.hpp"
#include "Network/NetworkMessage.hpp"

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
    for (auto& client : clients) {
        if (client.second.id == id) {
            ENet::DisconnectPeer(server.get(), client.first); // Если принудительно отсоединили кого-то, то onDisconnect у обоих сторон должен сработать
        }
    }
}

void Server::OnConnect(ENetPeer* peer) // Здесь сервер не меняет состояние он почти всегда просто IDLE
{
    auto p = connection_data_manager.GetFreeConnectionData();
    if (p.first)
    {
        auto player_data = SessionPlayerConnection{ p.second.id, p.second.spawn };
        peer -> data = new SessionPlayerConnection{ player_data }; // не бросайте в меня камни, это нормально если работаешь с Си API (ENet такой и есть)
        clients.emplace(peer, player_data);
    }
}

void Server::OnDisconnect(ENetPeer* peer)
{
    auto it = clients.find(peer);
    if (it != clients.cend())
    {
        connection_data_manager.ReleaseConnectionData(it -> second);
        delete static_cast<SessionPlayerConnection*>(peer -> data); // не кросайтесь бамнями
        clients.erase(peer);
    }
}

NetMsg Server::OnReceive(ENetPeer* peer, ENetPacket* packet) // а вот пакеты разные приходят
{
    if (clients.contains(peer))
    {
        return NetMsg{ MessageProcessor::Serialize(peer, packet) }; // явно NetMsg объект возвращаю чтоб повысить шансы на RVO
    }
    return NetMsg{ std::nullopt };
}

void Server::SendToClient(const NetworkMessage& msg, uint8_t id, float dt) // это избранные данные клиентам передавать
{
    EasyBytes bytes;
    bytes.Write(msg.type);
    bytes.Write(msg.payload.Data(), msg.payload.Size());

    ENetPeer* peer = nullptr;
    for (auto& client : clients) {
        if (client.second.id == id) {
            peer = client.first;
            break;
        }
    }
    
    accum += dt;
    if (accum >= tickRate) {
        ENet::SendPacketToPeer(peer, bytes.Data(), bytes.Size());
        accum -= tickRate;
    }
}

void Server::SendBroadcast(const NetworkMessage& msg, float dt) // это для всех передавать одно и то же
{
    EasyBytes bytes;
    bytes.Write(msg.type);
    bytes.Write(msg.payload.Data(), msg.payload.Size());

    accum += dt;
    if (accum >= tickRate) {
        ENet::SendFromHostBroadcast(server.get(), bytes.Data(), bytes.Size());
        accum -= tickRate;
    }
}

MsgQueue Server::PollEvents()
{
    return ENet::PollEvents(server.get(), *this);
}