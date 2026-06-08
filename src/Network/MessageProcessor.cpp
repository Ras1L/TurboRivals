#include "Network/MessageProcessor.hpp"
#include "Core/EasyBytes.hpp"
#include "Core/Input.hpp"
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
        auto p = Deserialize(msg);
        switch (msg.type)
        {
            case PacketType::SessionState: {
                auto new_session = std::get<packet_traits_t<PacketType::SessionState>>(p); // все возьму от сервера кроме my_id
                session.track   = new_session.track;
                session.env     = new_session.env;
                session.players = std::move(new_session.players);
                break;
            }
            case PacketType::ClientConfig: {
                auto data = msg.peer -> data;
                if (!data) {
                    fprintf(stderr, "WARNING: ENET: MessageProcessor: Packet received from dead peer\n");
                }
                auto peer_data = static_cast<SessionPlayerConnection*>(data);

                auto id    = peer_data -> id;
                auto car   = std::get<packet_traits_t<PacketType::ClientConfig>>(p).car;
                auto spawn = peer_data -> spawn;
                
                session.players[id] = {true, id, car, spawn};
                break;
            }
            case PacketType::PlayerID:
                session.my_id = std::get<packet_traits_t<PacketType::PlayerID>>(p);
                break;
            default:
                break;
        }
        queue.pop();
    }
    return session;
}

SessionStateRuntime MessageProcessor::ApplyChanges(SessionStateRuntime& session, MsgQueue& queue)
{
    while (!queue.empty())
    {
        auto msg = queue.front();
        auto p = Deserialize(msg);
        switch (msg.type)
        {
            case PacketType::SessionStateRuntime:
                session = std::get<packet_traits_t<PacketType::SessionStateRuntime>>(p);
                break;
            case PacketType::VehicleInput: {
                auto data = msg.peer -> data;
                if (!data) {
                    fprintf(stderr, "WARNING: ENET: MessageProcessor: Packet received from dead peer\n");
                }
                auto id = static_cast<SessionPlayerConnection*>(data) -> id;

                session.players[id].input = std::get<packet_traits_t<PacketType::VehicleInput>>(p);
                break;
            }
            default:
                break;
        }
        queue.pop();
    }
    return session;
}

NetworkMessage MessageProcessor::Serialize(const PacketVariant& packet) // вместо кучи перегрузок я ввел std::variant
{
    NetworkMessage msg;

    std::visit(overloaded {
        [&msg](const VehicleInput& input){
            msg.type = PacketType::VehicleInput;
            msg.payload.Write(input);
        },
        [&msg](const SessionStateRuntime& session){
            msg.type = PacketType::SessionStateRuntime;
            msg.payload.Write(session.players.size());
            for (auto& player : session.players) {
                msg.payload.Write(player);
            }
        },
        [&msg](const SessionPlayerChoice& car){
            msg.type = PacketType::ClientConfig;
            msg.payload.Write(car);
        },
        [&msg](const SessionState& session){
            msg.type = PacketType::SessionState;
            msg.payload.Write(session.track);
            msg.payload.Write(session.env);
            for (auto& player : session.players) {
                msg.payload.Write(player);
            };
        },
        [&msg](const id_type id){
            msg.type = PacketType::PlayerID;
            msg.payload.Write(id);
        }
    }, packet);

    return msg;
}

PacketVariant MessageProcessor::Deserialize(const NetworkMessage& msg) // вместо кучи перегрузок я ввел std::variant
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
            for (auto& player : session.players) {
                player = msg.payload.Read<std::remove_reference_t<decltype(player)>>();
            }
            msg.payload.ResetOffset();

            return PacketVariant{ session };
        }

        case PacketType::PlayerID: {
            id_type id;
            id = msg.payload.Read<packet_traits_t<PacketType::PlayerID>>();
            msg.payload.ResetOffset();

            return PacketVariant{ id };
        }

        case PacketType::None:
            break;
    }
    return PacketVariant{};
}

NetMsg MessageProcessor::Serialize(ENetPeer* peer, ENetPacket* packet)
{
    NetworkMessage msg;
    if (packet -> data != nullptr && packet -> dataLength > 0) {
        EasyBytes data(packet -> data, packet -> dataLength);
        msg.peer    = peer;
        msg.type    = data.Read<decltype(msg.type)>();
        msg.payload = data.Read();
        data.ResetOffset();
    
        return NetMsg{ msg };
    }
    return NetMsg{ std::nullopt };
}