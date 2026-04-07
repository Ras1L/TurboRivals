#include "UI/InputManager.hpp"
#include "raylib.h"

Input InputManager::GetInput() {
    input.sideway = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    input.forward = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    input.brake   = IsKeyDown(KEY_SPACE);
    
    return input;
}