#include "Network/Client.hpp"
#include "Network/ENet.hpp"
#include "Network/NetworkMessage.hpp"
#include "enet/enet.h"
#include "enet/types.h"
#include <cstring>

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

void Client::OnConnect(ENetPeer* peer) // к клиенту не подключаются, он подключается к серверу
{
    (void) peer;
}

void Client::OnDisconnect(ENetPeer* peer) // не знаю что делать, если клиента отсоединили
{
    (void) peer;
}

NetMsg Client::OnReceive(ENetPeer* peer, ENetPacket* packet) // а вот пакеты разные приходят
{
    if (peer == server.get()) // мало ли кто пришел, может мы его не знаем
    {
        if (packet -> dataLength > 0) {
            NetworkMessage msg;

            auto type_size = sizeof(msg.type); // пока type_size это 1 байт, т. к. uint8_t
            std::memcpy(&msg.type, packet -> data, type_size);

            auto payload_size = packet -> dataLength - type_size;
            if (payload_size > 0) {
                msg.payload.resize(payload_size);
                auto payload_ptr = static_cast<uint8_t*>(packet -> data) + type_size; // нужно привести void* к другому типу* чтоб сдвинуть
                std::memcpy(msg.payload.data(), payload_ptr, payload_size);

                return msg;
            }
        }
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

NetMsg Client::Receive(enet_uint32 ms)
{
    return ENet::PollEvents(client.get(), *this, ms);
}

void Client::Update()
{
    ENet::PollEvents(client.get(), *this, 0);
}