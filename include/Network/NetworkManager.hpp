#ifndef NETWORK_NETWORK_MANAGER_HPP
#define NETWORK_NETWORK_MANAGER_HPP

#include "Network/INetworkListener.hpp"

#include <enet/enet.h>
#include <memory>

const float       tickRate     = 1.f/60.f;
const std::string DEFAULT_IP   = "127.0.0.1";
const uint16_t    DEFAULT_PORT = 7903;

struct ENetHostDeleter {
    void operator()(ENetHost* server) {
        enet_host_destroy(server);
    }
};

using Addr = ENetAddress;
using Host = std::unique_ptr<ENetHost, ENetHostDeleter>;
using Peer = std::unique_ptr<ENetPeer>;

class NetworkManager {
public:
    void Init();
    void Deinit();

    static Host CreateServer(ENetAddress* address, std::string ip = DEFAULT_IP, uint16_t port = DEFAULT_PORT);
    static Host CreateClient();
    static void DestroyHost(ENetHost* host);

    static Peer ConnectToPeer(ENetHost* host, ENetAddress* address);
    static void DisconnectPeer(ENetHost* host, ENetPeer* peer); // peer отсоединяем от host

    static void PollEvents(ENetHost* host, INetworkListener& listener);

    static void SendPacketToPeer(ENetPeer* peer);
    static void SendFromHostBroadcast(ENetHost* server);
};

#endif