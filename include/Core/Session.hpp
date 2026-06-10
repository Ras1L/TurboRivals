#ifndef CORE_SESSION_HPP
#define CORE_SESSION_HPP

#include "Core/Input.hpp"
#include "Core/ModelID.hpp"
#include "Core/Transform3D.hpp"
#include "raylib.h"

#include <cstdint>
#include <vector>
#include <optional>

constexpr size_t MAX_PLAYERS = 8;

using id_type = uint8_t;

struct SessionPlayer { // все об игроке в лобби
    bool is_active = false;
    id_type id;
    ModelID car;
    Vector3 spawn;
};

struct SessionPlayerChoice { // что клиент может контролировать
    ModelID car;
};

struct SessionPlayerConnection { // что сервер контролирует
    id_type id;
    Vector3 spawn;
};

struct SessionState {
    id_type my_id;
    ModelID track;
    ModelID env;
    std::vector<SessionPlayer> players{ MAX_PLAYERS };
};

struct SessionPlayerRuntime {
    SessionPlayer info;
    Transform3D   trans = Transform3D::Identity();
    VehicleInput  input;
};

struct SessionStateRuntime {
    id_type my_id;
    std::vector<SessionPlayerRuntime> players{ MAX_PLAYERS };
};

using Session = std::optional<SessionState>;
using SessionRuntime = std::optional<SessionStateRuntime>;

#endif