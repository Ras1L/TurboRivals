#include "Network/Client.hpp"
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
    ENet::DestroyHost(client.get());
}

void Client::ConnectToServer(std::string ip)
{
    ENet::SetAddressIP(&server_addr, ip);
    if (server) { DisconnectFromServer(); }
    server = ENet::ConnectToPeer(client.get(), &server_addr);
}

void Client::DisconnectFromServer()
{
    ENet::DisconnectPeer(client.get(), server.get());
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
    if (peer == server.get()) // мало ли кто пришел, может мы его не знаем
    {
        return MessageProcessor::Serialize(packet);
    }
    return std::nullopt;
}

void Client::SendToServer(float dt)
{
    // TODO: формируем пакет, просто PlayerInput, шлём серверу
    // отдадим NetworkManager массив байт, его длину, а в массив байт еще запишем тип пакета

    accum += dt;
    if (accum >= tickRate)
    {
        ENet::SendPacketToPeer(server.get());
    }
    accum -= tickRate;
}

MsgQueue Client::PollEvents()
{
    return ENet::PollEvents(client.get(), *this, 0);
}