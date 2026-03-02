#include "raylib.h"
#include <cstdlib>
extern "C" { 
    #include <enet/enet.h>
}
#include <iostream>

const int SCREEN_WIDTH  = 1920;
const int SCREEN_HEIGHT = 1080;
const int TARGET_FPS    = 60;

void UpdateDrawFrame();

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TurboRivals");
    SetTargetFPS(TARGET_FPS);

    if (enet_initialize() != 0) {
        std::cerr << "An error occurred while initializing ENet.\n";
        return EXIT_FAILURE;
    }

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();

    atexit(enet_deinitialize);

    return EXIT_SUCCESS;
}

void UpdateDrawFrame()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Turbo Rivals", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2, 40, RED);
    EndDrawing();
}