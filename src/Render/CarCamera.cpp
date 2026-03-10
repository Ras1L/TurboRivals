#include "Render/CarCamera.hpp"
#include "raymath.h"

const Vector3 up{ 0.0f, 1.0f, 0.0f };
const Vector3 targetOffset{ 0.0f, 0.0f, -1.0f };
const float   BOTTOM_HEIGHT = 5.f;

static Vector2 lean = { 0 };
static float headTimer = 0.0f;
static float walkLerp = 0.0f;

CarCamera::CarCamera()
{
    camera.position = { 0 };
    camera.target = {0.f, 0.f, 0.f};
    camera.up = {0.f, 1.f, 0.f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void CarCamera::UpdateCamera(Vector2 lookRotation)
{
     // Left and right
    Vector3 yaw = Vector3RotateByAxisAngle(targetOffset, up, lookRotation.x);

    // Clamp view up
    float maxAngleUp = Vector3Angle(up, yaw);
    maxAngleUp -= 0.001f; // Avoid numerical errors
    if ( -(lookRotation.y) > maxAngleUp) { lookRotation.y = -maxAngleUp; }

    // Clamp view down
    float maxAngleDown = Vector3Angle(Vector3Negate(up), yaw);
    maxAngleDown *= -1.0f; // Downwards angle is negative
    maxAngleDown += 0.001f; // Avoid numerical errors
    if ( -(lookRotation.y) < maxAngleDown) { lookRotation.y = -maxAngleDown; }

    // Up and down
    Vector3 right = Vector3Normalize(Vector3CrossProduct(yaw, up));

    // Rotate view vector around right axis
    float pitchAngle = -lookRotation.y - lean.y;
    pitchAngle = Clamp(pitchAngle, -PI/2 + 0.0001f, PI/2 - 0.0001f); // Clamp angle so it doesn't go past straight up or straight down
    Vector3 pitch = Vector3RotateByAxisAngle(yaw, right, pitchAngle);

    // Head animation
    // Rotate up direction around forward axis
    float headSin = sinf(headTimer*PI);
    float headCos = cosf(headTimer*PI);
    const float stepRotation = 0.01f;
    camera.up = Vector3RotateByAxisAngle(up, pitch, headSin*stepRotation + lean.x);

    // Camera BOB
    const float bobSide = 0.1f;
    const float bobUp = 0.15f;
    Vector3 bobbing = Vector3Scale(right, headSin*bobSide);
    bobbing.y = fabsf(headCos*bobUp);

    camera.position = Vector3Add(camera.position, Vector3Scale(bobbing, walkLerp));
    camera.target = Vector3Add(camera.position, pitch);
}

void CarCamera::UpdateCameraPos(Vector3 pos)
{
    camera.position = {
        pos.x,
        pos.y + BOTTOM_HEIGHT,
        pos.z
    };
}