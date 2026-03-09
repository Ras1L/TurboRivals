#ifndef CORE_CARMOVEMENT_HPP
#define CORE_CARMOVEMENT_HPP

#include "raylib.h"

struct CarMovement {
    Vector3 position;
    Vector3 velocity;
    Vector3 dir;
};

#endif