#include "UI/InputManager.hpp"
#include "raylib.h"

PlayerInput InputManager::GetInput() {
    input.vehicle.sideway = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    input.vehicle.forward = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    input.vehicle.brake   = IsKeyDown(KEY_SPACE);
    
    input.vehicle.returnBack = IsKeyDown(KEY_R);

    input.camera.cameraLookBack = IsKeyPressed(KEY_DOWN) ? !input.camera.cameraLookBack : input.camera.cameraLookBack;
    input.camera.cameraRight    = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
    
    return input;
}