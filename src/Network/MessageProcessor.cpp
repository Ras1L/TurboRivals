#include "Network/MessageProcessor.hpp"
#include "Core/EasyBytes.hpp"
#include "Core/Input.hpp"
#include "Core/ModelID.hpp"
#include "Core/Session.hpp"
#include "Network/NetworkMessage.hpp"
#include "Network/PacketType.hpp"
#include <optional>
#include <type_traits>


SessionState MessageProcessor::ApplyChanges(SessionState& session, MsgQueue& queue)
{
    while (!queue.empty())
    {
        auto msg = queue.front();
        auto p = Deserialize(msg, true);
        switch (msg.type)
        {
            case PacketType::SessionState:
                session = std::get<std::remove_reference_t<decltype(session)>>(p);
                break;
            case PacketType::ClientConfig:
                session.players.resize(session.players.size() + 1);
                session.players.push_back({0, std::get<packet_traits_t<PacketType::ClientConfig>>(p)}); // id и spawn должны назначить мы
                break;
            default:
                break;
        }
    }
    return session;
}

SessionStateRuntime MessageProcessor::ApplyChanges(SessionStateRuntime& session, MsgQueue& queue)
{
    while (!queue.empty())
    {
        auto msg = queue.front();
        auto p = Deserialize(msg, true);
        switch (msg.type)
        {
            case PacketType::SessionStateRuntime:
                session = std::get<std::remove_reference_t<decltype(session)>>(p);
                break;
            case PacketType::VehicleInput:
                for (auto& player : session.players) {
                    player.input = std::get<decltype(player.input)>(p);
                }
                break;
            default:
                break;
        }
    }
    return session;
}

NetworkMessage MessageProcessor::Serialize(const PacketVariant& packet) // вместо кучи перегрузок я ввел std::variant
{
    NetworkMessage msg;

    std::visit(overloaded {
        [&msg](const VehicleInput& input){
            msg.payload.Write(input);
        },
        [&msg](const SessionStateRuntime& session){
            msg.payload.Write(session.players.size());
            for (auto& player : session.players) {
                msg.payload.Write(player);
            }
        },
        [&msg](const ModelID& car){
            msg.payload.Write(car);
        },
        [&msg](const SessionState& session){
            msg.payload.Write(session.track);
            msg.payload.Write(session.env);
            msg.payload.Write(session.players.size());
            for (auto& player : session.players) {
                msg.payload.Write(player);
            };
        },
    }, packet);

    return msg;
}

PacketVariant MessageProcessor::Deserialize(const NetworkMessage& msg, bool) // вместо кучи перегрузок я ввел std::variant
{
    switch (msg.type)
    {
        case PacketType::VehicleInput: {
            auto input = msg.payload.Read<packet_traits_t<PacketType::VehicleInput>>();
            msg.payload.ResetOffset();
            return PacketVariant{ input };
        }

        case PacketType::SessionStateRuntime: {
            SessionStateRuntime session;
            session.players.resize(msg.payload.Read<decltype(session.players.size())>());
            for (auto& player : session.players) {
                player = msg.payload.Read<std::remove_reference_t<decltype(player)>>();
            }
            msg.payload.ResetOffset();
            return PacketVariant{ session };
        }

        case PacketType::ClientConfig: {
            auto config = msg.payload.Read<packet_traits_t<PacketType::ClientConfig>>();
            msg.payload.ResetOffset();
            return PacketVariant{ config };
        }

        case PacketType::SessionState: {
            SessionState session;
            session.track = msg.payload.Read<decltype(session.track)>();
            session.env   = msg.payload.Read<decltype(session.env)>();

            session.players.resize(msg.payload.Read<decltype(session.players.size())>()); // Write должен быть таким же по порядку
            for (auto& player : session.players) {
                player = msg.payload.Read<std::remove_reference_t<decltype(player)>>();
            }
            msg.payload.ResetOffset();

            return PacketVariant{ session };
        }

        case PacketType::None:
            break;
    }
    return PacketVariant{};
}

NetMsg MessageProcessor::Serialize(ENetPacket* packet)
{
    NetMsg msg;
    if (packet -> data != NULL && packet -> dataLength > 0) {
        EasyBytes data(packet -> data, packet -> dataLength);
        msg -> type    = data.Read<decltype(msg -> type)>();
        msg -> payload = data.Read();
        data.ResetOffset();
    
        return msg;
    }
    return std::nullopt;
}