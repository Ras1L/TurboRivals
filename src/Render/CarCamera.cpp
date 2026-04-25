#include "Render/CarCamera.hpp"

#include "raylib.h"
#include "raymath.h"

const float cameraOffsetZ       = 13.f;
const float cameraRightStrength = 6.f;
Vector3 cameraOffset{ 0.f, 5.f, cameraOffsetZ};

CarCamera::CarCamera()
{
    camera.position = { 0 };
    camera.target = {0.f, 0.f, 0.f};
    camera.up = {0.f, 1.f, 0.f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void CarCamera::UpdateCameraTransform(const Input& input, Transform3D transform, float dt)
{
    cameraOffset.x += input.cameraRight * dt * cameraRightStrength;
    if (input.cameraLookBack) {
        cameraOffset.z = -cameraOffsetZ;
    } else {
        cameraOffset.z = cameraOffsetZ;
    }

    Matrix rotation = QuaternionToMatrix(transform.rot);

    Vector3 forward = Vector3Normalize(Vector3Transform({0.f, 0.f, -1.f}, rotation));
    Vector3 up      = Vector3Normalize(Vector3Transform({0.f, 1.f, 0.f}, rotation));

    Vector3 rotatedOffset = Vector3RotateByQuaternion(cameraOffset, transform.rot);

    camera.position = Vector3Add(transform.pos, rotatedOffset);
    if (!input.cameraLookBack) {
        camera.target = Vector3Add(camera.position, forward);
    } else {
        camera.target = Vector3Add(camera.position, Vector3Negate(forward));
    }
    camera.up = up;
}