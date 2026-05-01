#ifndef NETWORK_NETWORK_MANAGER_HPP
#define NETWORK_NETWORK_MANAGER_HPP

#include <enet/enet.h>
#include <memory>

#include "Network/INetworkListener.hpp"

const float tickRate = 1.f/60.f;

struct ENetHostDeleter {
    void operator()(ENetHost* server) {
        enet_host_destroy(server);
    }
};

using Host = std::unique_ptr<ENetHost, ENetHostDeleter>;
using Peer = std::unique_ptr<ENetPeer>;

class NetworkManager {
public:
    void Init();
    void Deinit();

    static Host CreateServer(ENetAddress* address, std::string ip = "127.0.0.1", unsigned short port = 7903);
    static Host CreateClient();
    static void DestroyHost(ENetHost* host);

    static Peer ConnectToPeer(ENetHost* host, ENetAddress* address);
    static void DisconnectPeer(ENetHost* host, ENetPeer* peer); // peer отсоединяем от host

    void PollEvents(ENetHost* host, INetworkListener& listener);

    static void SendPacketToPeer(ENetPeer* peer);
    static void SendFromHostBroadcast(ENetHost* server);
};

#endif