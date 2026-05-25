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
            node -> status = NetworkStatus::NONE;
            break;

        case NetworkRole::CLIENT:
            ENet::Initialize();
            {
                auto p = std::make_unique<Client>();
                node.reset(p.get());
                node -> Init();
                client = p.get();

                node -> status = NetworkStatus::IDLE;
            }
            break;

        case NetworkRole::SERVER:
            ENet::Initialize();
            {
                auto p = std::make_unique<Server>();
                node.reset(p.get());
                node -> Init();
                server = p.get();

                node -> status = NetworkStatus::IDLE;
            }
            break;
    }
}

void NetworkManager::Deinit()
{
    if (node) {
        node -> Destroy();
        ENet::Deinitialize();
    }
    node -> status = NetworkStatus::NONE;
}

void NetworkManager::Connect(std::string ip)
{
    if (node) {
        if (client) {
            client -> ConnectToServer(ip);
        }
    }
}

MsgQueue NetworkManager::Update(float dt)
{
    MsgQueue queue = PollEvents(); // Обработка событий
    SendOutgoing(dt);             // Генерация событий
    return queue;
}

MsgQueue NetworkManager::PollEvents()
{
    MsgQueue queue;
    if (node) {
        queue = node -> PollEvents();
    }
    return queue;
}

void NetworkManager::SendOutgoing(float dt)
{
    if (node) {
        if (client) {
            if (node -> status == NetworkStatus::PLAYING) { // TODO: Отправлять разные пакеты
                client -> SendToServer(dt);
            } else
            if (node -> status == NetworkStatus::CONNECTED) { // Идет синхронизация
                client -> SendToServer(dt);
            }
        } else
        if (server) {
            if (node -> status == NetworkStatus::PLAYING) {
                server -> SendToClients(dt);
            } else
            if (node -> status == NetworkStatus::IDLE) {
                server -> SendBroadcast(dt);
            }
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