#include "UI/Window.hpp"

#include "raylib.h"

void Window::create()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TurboRivals");
    DisableCursor();
    SetTargetFPS(TARGET_FPS);
}

void Window::close()
{
    CloseWindow();
}