#ifndef NETWORK_INETWORK_LISTENER_HPP
#define NETWORK_INETWORK_LISTENER_HPP

#include <enet/enet.h>

class INetworkListener {
public:
    virtual void OnConnect(ENetPeer* peer)                     = 0;
    virtual void OnDisconnect(ENetPeer* peer)                  = 0;
    virtual void OnReceive(ENetPeer* peer, ENetPacket* packet) = 0;
};

#endif