#include "Render/CarCamera.hpp"

#include "raylib.h"
#include "raymath.h"

const Vector3 cameraOffset{ 0.f, 10.f, 25.f};

CarCamera::CarCamera()
{
    camera.position = { 0 };
    camera.target = {0.f, 0.f, 0.f};
    camera.up = {0.f, 1.f, 0.f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void CarCamera::UpdateCameraTransform(Transform3D transform)
{
    Matrix rotation = QuaternionToMatrix(transform.rot);

    Vector3 forward = Vector3Normalize(Vector3Transform({0.f, 0.f, -1.f}, rotation));
    Vector3 up      = Vector3Normalize(Vector3Transform({0.f, 1.f, 0.f}, rotation));

    Vector3 rotatedOffset = Vector3RotateByQuaternion(cameraOffset, transform.rot);

    camera.position = Vector3Add(transform.pos, rotatedOffset);
    camera.target   = Vector3Add(camera.position, forward);
    camera.up       = up;
}