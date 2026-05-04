#include "Network/Client.hpp"
#include "Network/ENet.hpp"
#include "Network/PacketType.hpp"
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
    enet_address_set_host(&server_addr, ip.c_str()); // не буду проверять успешно или нет
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

void Client::OnReceive(ENetPeer* peer, ENetPacket* packet) // а вот пакеты разные приходят
{
    if (peer == server.get()) // мало ли кто пришел, может мы его не знаем
    {
        PacketType pt = static_cast<PacketType>(packet -> data[0]);
        switch (pt) 
        {
            case PacketType::CurrentTransforms:
                // TODO: пакет пришедший интерпретировать как массив трансформов для машин и возвращать нужный
                // или сделать чтоб сервер избранно отправлял пакеты клиентам и возвращать std::optional<Transform3D> здесь
                return;

            default:
                break;
        }
    }
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

void Client::Update()
{
    ENet::PollEvents(client.get(), *this);
}