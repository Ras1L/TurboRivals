#ifndef CORE_TRANSFORM3D_HPP
#define CORE_TRANSFORM3D_HPP

#include "raylib.h"

struct Transform3D {
    Vector3    pos;
    Quaternion rot;
};

#endif