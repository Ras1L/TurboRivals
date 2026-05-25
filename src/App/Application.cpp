#include "App/Application.hpp"
#include "App/MenuScene.hpp"
#include "raylib.h"

void Application::exec()
{
    window.Create();
    scene_manager.Set<MenuScene>(context.network);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        scene_manager.Update(dt);

        BeginDrawing();
        ClearBackground(SKYBLUE);
        scene_manager.Render();
        EndDrawing();
    }

    scene_manager.Reset();
    window.Close();
}