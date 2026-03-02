#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int TARGET_FPS = 60;

void UpdateDrawFrame();

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TurboRivals");
    
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();

    return 0;
}

void UpdateDrawFrame()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Turbo Rivals", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2, 40, RED);
    EndDrawing();
}