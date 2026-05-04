#ifndef NETWORK_ENET_HPP
#define NETWORK_ENET_HPP

#include "Network/INetworkNode.hpp"

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

    using Addr = ENetAddress;
    using Host = std::unique_ptr<ENetHost, ENetHostDeleter>;
    using Peer = std::unique_ptr<ENetPeer>;
    using Node = std::unique_ptr<INetworkNode>;

    void Initialize();
    void Deinitialize();

    Host CreateServer(ENetAddress* address, std::string ip = DEFAULT_IP, uint16_t port = DEFAULT_PORT);
    Host CreateClient();
    void DestroyHost(ENetHost* host);

    Peer ConnectToPeer(ENetHost* host, ENetAddress* address);
    void DisconnectPeer(ENetHost* host, ENetPeer* peer); // peer отсоединяем от host

    void PollEvents(ENetHost* host, INetworkNode& listener);

    void SendPacketToPeer(ENetPeer* peer);
    void SendFromHostBroadcast(ENetHost* server);
}


#endif