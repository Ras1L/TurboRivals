#include "Network/Client.hpp"
#include "Core/EasyBytes.hpp"
#include "Network/ENet.hpp"
#include "Network/MessageProcessor.hpp"
#include "Network/NetworkMessage.hpp"
#include "Network/NetworkStatus.hpp"
#include "enet/enet.h"

void Client::Init()
{
    client = ENet::CreateClient();
}

void Client::Destroy()
{
    if (is_connected) {
        DisconnectFromServer();
    }
    ENet::DestroyHost(client.get());
}

bool Client::ConnectToServer(std::string ip)
{
    if (server) { DisconnectFromServer(); }

    ENet::SetAddressIP(&server_addr, ip);
    server = ENet::ConnectToPeer(client.get(), &server_addr);
    if (!server) {
        return false;
    }
    is_connected = true;
    return is_connected;
}

void Client::DisconnectFromServer()
{
    if (server && client) {
        ENet::DisconnectPeer(client.get(), server);
        is_connected = false;
    }
}

void Client::OnConnect(ENetPeer* peer) // если клиент подключился к серверу
{
    (void) peer;
    status = NetworkStatus::CONNECTED;
}

void Client::OnDisconnect(ENetPeer* peer) // если отсоединили или отсоединился
{
    (void) peer;
    status = NetworkStatus::DISCONNECTED;
}

NetMsg Client::OnReceive(ENetPeer* peer, ENetPacket* packet) // а вот пакеты разные приходят
{
    if (peer == server) // мало ли кто пришел, может мы его не знаем
    {
        return MessageProcessor::Serialize(peer, packet);
    }
    return std::nullopt;
}

void Client::SendToServer(const NetworkMessage& msg, float dt)
{
    if (is_connected)
    {
        EasyBytes bytes;
        bytes.Write(msg.type);
        bytes.Write(msg.payload.Data(), msg.payload.Size());
    
        accum += dt;
        if (accum >= tickRate) {
            ENet::SendPacketToPeer(server, bytes.Data(), bytes.Size());
            accum -= tickRate;
        }
    }
}

MsgQueue Client::PollEvents()
{
    if (is_connected) {
        return ENet::PollEvents(client.get(), *this);
    }
    return MsgQueue{};
}