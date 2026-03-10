#include "UI/InputManager.hpp"

const Vector2 sensitivity{ 0.001f, 0.001f };

Input InputManager::GetInput() {
    Vector2 mouseDelta = GetMouseDelta();
    input.lookRotation.x -= mouseDelta.x*sensitivity.x;
    input.lookRotation.y += mouseDelta.y*sensitivity.y;

    input.sideway = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
    input.forward = (IsKeyDown(KEY_W)) - IsKeyDown(KEY_S);

    return input;
}