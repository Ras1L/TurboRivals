#include "Network/Client.hpp"
#include "Network/NetworkManager.hpp"
#include "enet/enet.h"


void Client::Init()
{
    client = NetworkManager::CreateClient();
}

void Client::Destroy()
{
    NetworkManager::DestroyHost(client.get());
}

void Client::ConnectToServer(ENetAddress* const address)
{
    server = NetworkManager::ConnectToPeer(client.get(), address);
}

void Client::DisconnectFromServer()
{
    NetworkManager::DisconnectPeer(client.get(), server.get());
}