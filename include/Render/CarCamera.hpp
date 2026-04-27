#ifndef RENDER_CARCAMERA_HPP
#define RENDER_CARCAMERA_HPP

#include "Core/Transform3D.hpp"
#include "Core/Input.hpp"

#include "raylib.h"

class CarCamera {
public:
    Camera3D camera;

    CarCamera();
    void UpdateCameraTransform(const CameraInput& input, Transform3D transform, float dt);
};

#endif