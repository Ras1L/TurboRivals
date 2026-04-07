#include "App/Application.hpp"
#include "Core/ModelID.hpp"
#include "raylib.h"

void Application::exec()
{
    window.create();
    physics.Init();
    res_manager.InitModels();
    player.model_id = ModelID::PORSCHE_911_CARRERA_993;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        auto input {input_manager.GetInput()};
        physics.Update(input.forward, input.brake, input.sideway, dt);
        player.transform = physics.GetVehicleTransform();

        car_camera.UpdateCameraTransform(player.transform);
        //car_camera.UpdateCamera(input.lookRotation);
        
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        BeginMode3D(car_camera.camera);
            car_renderer.DrawCar(player, res_manager);
            level_renderer.DrawLevel();
        EndMode3D();

        EndDrawing();
    }

    res_manager.UnloadModels();
    window.close();
}