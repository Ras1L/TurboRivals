#include "App/Application.hpp"
#include "Core/GameWorld.hpp"
#include "Core/ModelID.hpp"
#include "raylib.h"

void Application::exec()
{
    window.Create();
    render.Init();
    
    Car* local_player = world.CreateCar(0.f,0.f, ModelID::PORSCHE_911_CARRERA_993);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        world.Update(input_manager.GetInput(), dt);
        car_camera.UpdateCameraTransform(local_player->physic_model.GetVehicleTransform());

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(car_camera.camera);
            render.DrawCar(*local_player);
            render.DrawEnvironment(EnvironmentID::SNOW);
        EndMode3D();

        EndDrawing();
    }

    render.Destroy();
    window.Close();
}