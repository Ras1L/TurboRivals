#include "App/Application.hpp"
#include "raylib.h"

void Application::exec()
{
    window.create();

    while (!WindowShouldClose())
    {
        Input input{ input_manager.GetInput() };
        physics.UpdateBody(player, input.lookRotation.x, input.forward, input.sideway);
        car_camera.UpdateCameraPos(player.position);
        car_camera.UpdateCamera(input.lookRotation);

        BeginDrawing();
        ClearBackground(RAYWHITE);


        BeginMode3D(car_camera.camera);
            level.DrawLevel();
        EndMode3D();

        EndDrawing();
    }

    window.close();
}