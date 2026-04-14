#include "App/Application.hpp"
#include "Core/Environment.hpp"
#include "Core/GameWorld.hpp"
#include "Core/ModelID.hpp"
#include "raylib.h"

void Application::exec()
{
    window.Create();
    render.Init();
    
    Car* local_player = world.CreateCar(0.f,0.f, ModelID::CAR__PORSCHE_911_CARRERA_993);
    Environment env{{ModelID::ENV__SNOW_MOUNTAINS}};

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        world.Update(input_manager.GetInput(), dt);
        car_camera.UpdateCameraTransform(local_player->vehicle_physics_comp.GetVehicleTransform());

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(car_camera.camera);
            render.DrawCar(*local_player);
            render.DrawEnvironment(env);
        EndMode3D();

        EndDrawing();
    }

    render.Destroy();
    window.Close();
}