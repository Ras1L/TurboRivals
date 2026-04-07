#ifndef RENDER_CARCAMERA_HPP
#define RENDER_CARCAMERA_HPP

#include "Core/Transform3D.hpp"

#include "raylib.h"

class CarCamera {
public:
    Camera3D camera;

    CarCamera();
    void UpdateCameraTransform(Transform3D transform);
};

#endif