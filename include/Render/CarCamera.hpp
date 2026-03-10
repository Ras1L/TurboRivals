#ifndef RENDER_CARCAMERA_HPP
#define RENDER_CARCAMERA_HPP

#include "raylib.h"

class CarCamera {
public:
    Camera3D camera;

    CarCamera();
    void UpdateCamera(Vector2 lookRotation);
    void UpdateCameraPos(Vector3 pos);
};

#endif