#ifndef NETWORK_ENET_HPP
#define NETWORK_ENET_HPP

#include "Network/INetworkNode.hpp"
#include "Network/NetworkMessage.hpp"
#include "enet/types.h"
#include <enet/enet.h>
#include <memory>

const float       tickRate     = 1.f/60.f;
const std::string DEFAULT_IP   = "127.0.0.1";
const uint16_t    DEFAULT_PORT = 7903;

namespace ENet
{
    struct ENetHostDeleter {
        void operator()(ENetHost* server) {
            enet_host_destroy(server);
        }
    };

    struct ENetPacketDeleter {
        void operator()(ENetPacket* packet) {
            enet_packet_destroy(packet);
        }
    };

    using Addr = ENetAddress;
    using Host = std::unique_ptr<ENetHost, ENetHostDeleter>;
    using Peer = std::unique_ptr<ENetPeer>;
    using Node = std::unique_ptr<INetworkNode>;
    using Packet = std::unique_ptr<ENetPacket, ENetPacketDeleter>; // для красоты, просто ENet иногда на себя ответственность берет за очистку пакетов

    void Initialize();
    void Deinitialize();

    Host CreateServer(ENetAddress* address, std::string ip = DEFAULT_IP, uint16_t port = DEFAULT_PORT);
    Host CreateClient();
    void DestroyHost(ENetHost* host);

    Peer ConnectToPeer(ENetHost* host, ENetAddress* address);
    void DisconnectPeer(ENetHost* host, ENetPeer* peer); // peer отсоединяем от host

    MsgQueue PollEvents(ENetHost* host, INetworkNode& listener, enet_uint32 ms);

    void SendPacketToPeer(ENetPeer* peer);
    void SendFromHostBroadcast(ENetHost* server);

    void SetAddressIP(ENetAddress* address, std::string ip);
}


#endif