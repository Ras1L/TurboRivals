#ifndef CORE_SESSION_HPP
#define CORE_SESSION_HPP

#include "Core/Input.hpp"
#include "Core/ModelID.hpp"
#include "raylib.h"

#include <cstdint>
#include <vector>
#include <optional>

constexpr size_t MAX_PLAYERS = 8;

struct SessionPlayer { // все об игроке в лобби
    bool is_active = false;
    uint8_t id;
    ModelID car;
    Vector3 spawn;
};

struct SessionPlayerChoice { // что клиент может контролировать
    ModelID car;
};

struct SessionPlayerConnection { // что сервер контролирует
    uint8_t id;
    Vector3 spawn;
};

struct SessionState {
    ModelID track;
    ModelID env;
    std::vector<SessionPlayer> players{ MAX_PLAYERS };
};

struct SessionPlayerRuntime {
    SessionPlayer player;
    Vector3       pos;
    VehicleInput  input;
};

struct SessionStateRuntime {
    std::vector<SessionPlayerRuntime> players;
};

using Session = std::optional<SessionState>;
using SessionRuntime = std::optional<SessionStateRuntime>;

#endif