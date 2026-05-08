#include "App/Application.hpp"
#include "raylib.h"

void Application::exec()
{
    window.Create();
    scene_manager.Set(Scene::MENU);

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