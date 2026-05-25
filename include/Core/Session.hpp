#ifndef CORE_SESSION_HPP
#define CORE_SESSION_HPP

#include "Core/ModelID.hpp"
#include "raylib.h"

#include <cstdint>
#include <vector>
#include <optional>

struct SessionPlayer {
    uint8_t id;
    ModelID car;
    Vector3 spawn;
};

struct SessionState {
    ModelID track;
    ModelID env;
    std::vector<SessionPlayer> players;
};

using Session = std::optional<SessionState>;

#endif