#ifndef CORE_BODY_HPP
#define CORE_BODY_HPP

#include "raylib.h"

struct Body {
    Vector3 position;
    Vector3 velocity;
    Vector3 dir;
};

#endif