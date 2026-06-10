#ifndef CORE_TRANSFORM3D_HPP
#define CORE_TRANSFORM3D_HPP

#include "raylib.h"
#include "raymath.h"

struct Transform3D {
    Vector3    pos;
    Quaternion rot;

    static Transform3D Identity() {
        return Transform3D {Vector3Zero(), QuaternionIdentity() };
    }
};

#endif