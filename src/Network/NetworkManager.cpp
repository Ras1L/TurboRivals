#include "Network/NetworkManager.hpp"
#include "Network/Client.hpp"
#include "Network/NetworkMessage.hpp"
#include "Network/NetworkStatus.hpp"
#include "Network/Server.hpp"
#include "Network/ENet.hpp"
#include "enet/types.h"

void NetworkManager::Init(NetworkStatus status)
{
    switch (status)
    {
        case NetworkStatus::OFFLINE:
            break;

        case NetworkStatus::CLIENT:
            ENet::Initialize();
            {
                auto p = std::make_unique<Client>();
                node.reset(p.get());
                node->Init();
                client = p.get();
            }
            break;

        case NetworkStatus::SERVER:
            ENet::Initialize();
            {
                auto p = std::make_unique<Server>();
                node.reset(p.get());
                node->Init();
                server = p.get();
            }
            break;
    }
}

void NetworkManager::Deinit()
{
    if (node) {
        node->Destroy();
        ENet::Deinitialize();
    }
}

void NetworkManager::Connect(std::string ip)
{
    if (node) {
        if (client) {
            client->ConnectToServer(ip);
        }
    }
}

void NetworkManager::Update(float dt)
{
    if (node) { 
        node->Update();
        if (client) {
            client->SendToServer(dt);
        }
        if (server) {
            server->SendToClients(dt);
        }
    }
}

NetMsg NetworkManager::WaitForStart(float seconds)
{
    auto ms = static_cast<enet_uint32>(seconds * 1000.f);
    if (node) {
        if (client) {
            client -> Receive(ms);
        }
        if (server) {
            server -> SendBroadcast(tickRate); // мы не внутри цикла чтоб дельту передавать
        }
    }
    return std::nullopt;
}