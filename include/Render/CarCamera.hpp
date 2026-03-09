#ifndef RENDER_CARCAMERA_HPP
#define RENDER_CARCAMERA_HPP

#include "Core/CarMovement.hpp"
#include "raylib.h"

const Vector3 up{ 0.0f, 1.0f, 0.0f };
const Vector3 targetOffset{ 0.0f, 0.0f, -1.0f };

static Vector2 lookRotation = { 0 };
static Vector2 lean = { 0 };
static float headTimer = 0.0f;
static float walkLerp = 0.0f;

const float BOTTOM_HEIGHT = 0.5f;

class CarCamera {
public:
    CarMovement car;
    Camera3D camera;

    CarCamera();
    void UpdateCamera();
};

#endif