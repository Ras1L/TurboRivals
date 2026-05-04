#ifndef NETWORK_INETWORK_NODE_HPP
#define NETWORK_INETWORK_NODE_HPP

#include <enet/enet.h>

class INetworkNode {
public:
    virtual void Init()    = 0;
    virtual void Destroy() = 0;
    virtual void Update()  = 0;

    virtual void OnConnect(ENetPeer* peer)                     = 0;
    virtual void OnDisconnect(ENetPeer* peer)                  = 0;
    virtual void OnReceive(ENetPeer* peer, ENetPacket* packet) = 0;
};

#endif