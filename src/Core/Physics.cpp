#include "Core/Physics.hpp"

#include "raymath.h"

const float CONTROL = 15.f;
const float FRICTION = 0.86f;
const float MAX_SPEED = 20.f;
const float MAX_ACCEL = 150.f;

void Physics::UpdateBody(Body& body, float rot, char forward, char sideway)
{
    Vector2 input{ (float)sideway, (float)-forward };

    // Slow down diagonal movement
    if ((sideway != 0) && (forward != 0)) input = Vector2Normalize(input);

    float delta = GetFrameTime();

    Vector3 front = { sinf(rot), 0.f, cosf(rot) };
    Vector3 right = { cosf(-rot), 0.f, sinf(-rot) };

    Vector3 desiredDir = { input.x*right.x + input.y*front.x, 0.0f, input.x*right.z + input.y*front.z, };
    body.dir = Vector3Lerp(body.dir, desiredDir, CONTROL*delta);

    float decel = FRICTION;
    Vector3 hvel = { body.velocity.x*decel, 0.0f, body.velocity.z*decel };

    float hvelLength = Vector3Length(hvel); // Magnitude
    if (hvelLength < (MAX_SPEED*0.01f)) hvel = { 0 };

    // This is what creates strafing
    float speed = Vector3DotProduct(hvel, body.dir);

    // Whenever the amount of acceleration to add is clamped by the maximum acceleration constant,
    // a Player can make the speed faster by bringing the direction closer to horizontal velocity angle
    // More info here: https://youtu.be/v3zT3Z5apaM?t=165
    float maxSpeed = MAX_SPEED;
    float accel = Clamp(maxSpeed - speed, 0.f, MAX_ACCEL*delta);
    hvel.x += body.dir.x*accel;
    hvel.z += body.dir.z*accel;

    body.velocity.x = hvel.x;
    body.velocity.z = hvel.z;

    body.position.x += body.velocity.x*delta;
    body.position.y += body.velocity.y*delta;
    body.position.z += body.velocity.z*delta;

    // Fancy collision system against the floor
    if (body.position.y <= 0.0f)
    {
        body.position.y = 0.0f;
        body.velocity.y = 0.0f;
    }
}