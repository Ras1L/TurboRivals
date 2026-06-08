#include "Network/NetworkManager.hpp"
#include "Network/Client.hpp"
#include "Network/NetworkMessage.hpp"
#include "Network/NetworkRole.hpp"
#include "Network/NetworkStatus.hpp"
#include "Network/Server.hpp"
#include "Network/ENet.hpp"

void NetworkManager::Init(NetworkRole role)
{
    switch (role)
    {
        case NetworkRole::OFFLINE:
            role = NetworkRole::OFFLINE;
            break;

        case NetworkRole::CLIENT:
            role = NetworkRole::CLIENT;
            ENet::Initialize();
            
            node = std::make_unique<Client>();
            node -> Init();
            client = dynamic_cast<Client*>(node.get());

            node -> status = NetworkStatus::IDLE;
            
            break;

        case NetworkRole::SERVER:
            role = NetworkRole::SERVER;
            ENet::Initialize();
            
            node = std::make_unique<Server>();
            node -> Init();
            server = dynamic_cast<Server*>(node.get());

            node -> status = NetworkStatus::IDLE;
            
            break;
    }
}

void NetworkManager::Deinit()
{
    if (node) {
        node -> Destroy();
        ENet::Deinitialize();
    }
}

bool NetworkManager::Connect(std::string ip)
{
    if (node) {
        if (client) {
            return client -> ConnectToServer(ip);
        }
        if (server) {
            return true;
        }
    }
    return false;
}

MsgQueue NetworkManager::Update(const NetworkMessage& msg, float dt)
{
    if (node)
    {
        MsgQueue queue = PollEvents(); // Обработка событий
        SendOutgoing(msg, dt);        // Генерация событий
        return queue;
    }
    return MsgQueue{};
}

MsgQueue NetworkManager::PollEvents()
{
    MsgQueue queue;
    if (node) {
        queue = node -> PollEvents();
    }
    return queue;
}

void NetworkManager::SendOutgoing(const NetworkMessage& msg, float dt)
{
    if (node) {
        if (client) {
            client -> SendToServer(msg, dt);
        } else
        if (server) {
            server -> SendBroadcast(msg, dt);
        }
    }
}

void NetworkManager::SetStatus(NetworkStatus status)
{
    if (node) {
        node -> status = status;
    }
}

NetworkStatus NetworkManager::GetStatus() const
{
    if (node) {
        return node -> status;
    }
    return NetworkStatus::NONE;
}

NetworkRole NetworkManager::GetRole() const
{
    return role;
}