#include "Network/MessageProcessor.hpp"
#include "Core/EasyBytes.hpp"
#include "Core/Session.hpp"
#include "Network/NetworkMessage.hpp"
#include "Network/PacketType.hpp"
#include <optional>
#include <type_traits>


SessionState MessageProcessor::ApplyChanges(SessionState& session, MsgQueue& queue)
{
    while (!queue.empty())
    {
        auto s = Deserialize(queue.front());
        if (s.has_value()) {
            session = s.value(); // Сейчас модель такая, что в пакете уже полностью готовый SessionState, а не по кусочкам, поэтому полностью меняем значение session
        }
        queue.pop();
    }
    return session;
}

NetMsg MessageProcessor::Serialize(ENetPacket* packet)
{
    NetMsg msg;
    if (packet -> data != NULL && packet -> dataLength > 0) {
        EasyBytes data(packet -> data, packet -> dataLength);
        msg -> type    = data.Read<decltype(msg -> type)>();
        msg -> payload = data;
        data.ResetOffset();
    
        return msg;
    }
    return std::nullopt;
}

Session MessageProcessor::Deserialize(const NetworkMessage &msg)
{
    if (msg.type == PacketType::ServerGameConfig)
    {
        SessionState session;
        session.track   = msg.payload.Read<decltype(session.track)>();
        session.env     = msg.payload.Read<decltype(session.env)>();

        session.players.resize(msg.payload.Read<decltype(session.players.size())>()); // Write должен быть таким же по порядку
        for (auto& player : session.players) {
            player = msg.payload.Read<std::remove_reference_t<decltype(player)>>();
        }
        msg.payload.ResetOffset();

        return session;
    }
    return std::nullopt;
}