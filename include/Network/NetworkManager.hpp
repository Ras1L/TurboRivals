#ifndef NETWORK_NETWORK_MANAGER_HPP
#define NETWORK_NETWORK_MANAGER_HPP

#include <enet/enet.h>
#include <memory>
#include <optional>

#include "Network/INetworkListener.hpp"

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

    static Host CreateHost(ENetAddress* address, std::optional<std::string> ip = std::nullopt, unsigned short port = 7903);
    static Host CreateClient();
    static void DestroyHost(ENetHost* host);

    static Peer ConnectToPeer(ENetHost* host, ENetAddress* address);
    static void DisconnectPeer(ENetHost* host, ENetPeer* peer); // peer отсоединяем от host

    void PollEvents(ENetHost* host, INetworkListener& listener);

    void SendPacketToPeer(ENetPeer* peer, float accum, float dt);
    void SendFromHostBroadcast(ENetHost* server, float accum, float dt);
};

#endif