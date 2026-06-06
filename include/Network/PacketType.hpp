#ifndef NETWORK_PACKET_TYPE_HPP
#define NETWORK_PACKET_TYPE_HPP

#include "Core/Input.hpp"
#include "Core/Session.hpp"
#include <cstdint>
#include <variant>

enum class PacketType : uint8_t
{
    None,

    VehicleInput,
    SessionStateRuntime,

    ClientConfig,
    SessionState,
};

using PacketVariant = std::variant
<
    VehicleInput,
    SessionStateRuntime,

    SessionPlayerChoice,
    SessionState
>;

template <PacketType P>
struct packet_traits;

template <> struct packet_traits<PacketType::VehicleInput> {
    using type = VehicleInput;
};
template <> struct packet_traits<PacketType::SessionStateRuntime> {
    using type = SessionStateRuntime;
};
template <> struct packet_traits<PacketType::ClientConfig> {
    using type = SessionPlayerChoice;
};
template <> struct packet_traits<PacketType::SessionState> {
    using type = SessionState;
};

template <PacketType P>
using packet_traits_t = packet_traits<P>::type;

template <class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

#endif