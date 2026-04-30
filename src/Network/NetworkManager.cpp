#include "Network/NetworkManager.hpp"
#include "Network/INetworkListener.hpp"
#include "enet/enet.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <optional>

const float tickRate = 1.f/60.f;

const bool network_debug = true;

const size_t IP_SIZE = 64;
char beauty_ip[IP_SIZE];

bool   enet_init_success      = true;
size_t clients_for_connection = 8;
size_t channels_used          = 2;

void NetworkManager::Init()
{
    if (enet_initialize() != 0) {
        fprintf(stderr, "ERROR: ENET: An error occurred while initializing ENet.\n");
        enet_init_success = false;
    }
}

void NetworkManager::Deinit()
{
    if (enet_init_success) {
        atexit(enet_deinitialize);
    }
}

Host NetworkManager::CreateHost(ENetAddress* address, std::optional<std::string> ip, unsigned short port)
{
    if (ip.has_value()) {
        if (enet_address_set_host(address, ip.value().c_str()) < 0) {
            fprintf(stderr, "ERROR: ENET: An error occurred while setting ENet host address.\n");
            address -> host = ENET_HOST_ANY;
        }
    } else {
        address -> host = ENET_HOST_ANY;
    }
    address -> port = port;

    Host server(enet_host_create(address, clients_for_connection, channels_used, 0, 0));
    if (!server) {
        fprintf(stderr, "ERROR: ENET: An error occurred while creating ENet host.\n");
    }
    return server;
}

void NetworkManager::DestroyHost(ENetHost* host)
{
    enet_host_destroy(host);
}

Host NetworkManager::CreateClient()
{
    return Host(enet_host_create(NULL, 1, 2, 0, 0)); // 1 выходящее соединение
}

Peer NetworkManager::ConnectToPeer(ENetHost* host, ENetAddress* address)
{
    ENetEvent event;

    Peer peer(enet_host_connect(host, address, 2, 0)); // 2 канала: 0 и 1
    if (!peer) {
        fprintf(stderr, "ERROR: ENET: No available peers for initiating an ENet connection.\n");
        return nullptr;
    }

    enet_address_get_host_ip(address, beauty_ip, IP_SIZE);
    if (enet_host_service(host, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        printf("INFO: ENET: Connection to %s:%u succeed",
            beauty_ip,
            host -> address.port
        );
        return peer;
    }
    else
    {
        // если 5 секунд в ожидании подключения прошли или соединение оборвалось
        // если особых событий или ошибок нет, то лучше перезапустить попытку соединиться
        enet_peer_reset(peer.get());
        printf("WARNING: ENET: Connection to %s:%u failed.",
            beauty_ip,
            host -> address.port
        );
        return nullptr;
    }
}

void NetworkManager::DisconnectPeer(ENetHost* host, ENetPeer* peer)
{
    ENetEvent event;
 
    enet_peer_disconnect(peer, 0);
    
    // Ждем 3 секунды чтобы соединение сбросилось успешно и пакеты отправленные уничтожились
    while (enet_host_service(host, &event, 3000) > 0)
    {
        switch (event.type)
        {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
        
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("INFO: ENET: Disconnection succeeded.\n");
                return;
            
            default: break;
        }
    }
    enet_peer_reset(peer); // Принудительно сбрасываем соединение, если за 3 секунды не получилось это сделать
}

void NetworkManager::PollEvents(ENetHost* host, INetworkListener& listener)
{
    ENetEvent event;

    while (enet_host_service(host, &event, 0) > 0) { // 0 в аргументах функции - ожидание события в мс, для игрового цикла лучше без задержек
        switch (event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                enet_address_get_host_ip(&event.peer -> address, beauty_ip, IP_SIZE);
                printf("INFO: ENET: A new client connected from %s:%u",
                    beauty_ip,
                    event.peer -> address.port
                );
                // Cледующая строка для того чтобы привязать некоторые данные к конкретному юзеру который присоединился
                // например это новый Игрок с каким то ником с какой то своей машиной
                // event.peer -> data = new Player(car);
                listener.OnConnect(event.peer);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                if (network_debug) {
                    enet_address_get_host_ip(&event.peer -> address, beauty_ip, IP_SIZE);
                    printf ("INFO: ENET: A packet of length %zu was received from %s on channel %u.\n",
                        event.packet -> dataLength,
                        beauty_ip,
                        event.channelID
                    );
                }
                // где то здесь будем читать данные с пакета
                listener.OnReceive(event.peer, event.packet);
                // пакет удаляем, он нам больше не нужен, а то займет память, тем более 60 пакетов таких в секунду
                enet_packet_destroy(event.packet); 
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                enet_address_get_host_ip(&event.peer -> address, beauty_ip, IP_SIZE);
                printf("INFO: ENET: A client from %s:%u disconnected",
                    beauty_ip,
                    event.peer -> address.port
                );
                listener.OnDisconnect(event.peer);
                break;
                
            case ENET_EVENT_TYPE_NONE: // тишина, делать нечего
                break;
        }
    }
}

void NetworkManager::SendPacketToPeer(ENetPeer* peer, float accum, float dt)
{
    accum += dt;
    if (accum >= tickRate) { // отправляем 60 раз в секунду
        ENetPacket* packet = enet_packet_create("packet", strlen("packet") + 1, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT); // пакет так создаем, enet сам его почистит
        enet_peer_send(peer, 0, packet); // отправляем пакет клиенту по каналу channelID = 0
    }
    accum -= tickRate;
}

void NetworkManager::SendFromHostBroadcast(ENetHost* server, float accum, float dt)
{
    accum += dt;
    if (accum >= tickRate) {
        ENetPacket* packet = enet_packet_create("packet", strlen("packet") + 1, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT); // "packet" это заглушка
        enet_host_broadcast(server, 0, packet);
    }
    accum -= tickRate;
}