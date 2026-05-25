#include "Render/CarCamera.hpp"

#include "raylib.h"
#include "raymath.h"

constexpr float cameraOffsetZ       = 13.f;
constexpr float cameraRightStrength = 6.f;
Vector3 cameraOffset{ 0.f, 5.f, cameraOffsetZ};

CarCamera::CarCamera()
{
    m_camera.position = { 0 };
    m_camera.target = {0.f, 0.f, 0.f};
    m_camera.up = {0.f, 1.f, 0.f};
    m_camera.fovy = 60.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
}

void CarCamera::Update(const CameraInput& input, Transform3D transform, float dt)
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

    m_camera.position = Vector3Add(transform.pos, rotatedOffset);
    if (!input.cameraLookBack) {
        m_camera.target = Vector3Add(m_camera.position, forward);
    } else {
        m_camera.target = Vector3Add(m_camera.position, Vector3Negate(forward));
    }
    m_camera.up = up;
}