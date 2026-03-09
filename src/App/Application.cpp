#include "App/Application.hpp"
#include "raylib.h"

Application::Application() : window(), level(), car_camera() {}

void Application::exec()
{
    window.create();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(car_camera.camera);
            level.DrawLevel();
        EndMode3D();

        EndDrawing();
    }

    window.close();
}