#include "UI/Window.hpp"

#include "raylib.h"

void Window::Create()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TurboRivals");
    DisableCursor();
    SetTargetFPS(TARGET_FPS);
}

void Window::Close()
{
    CloseWindow();
}