#include "App/Application.hpp"
#include "Core/Environment.hpp"
#include "Core/GameWorld.hpp"
#include "Core/ModelID.hpp"
#include "raylib.h"

void Application::exec()
{
    window.Create();
    res_manager.InitModels();
    
    Car*        local_player = world.CreateCar(0.f, 0.f, ModelID::CAR__PORSCHE_911_CARRERA_993);
    Track*      track        = world.CreateTrack(res_manager.GetCollisionMeshDataByID(ModelID::TRK__CIRCUIT8_BRIDGE), ModelID::TRK__CIRCUIT8_BRIDGE);
    Environment env          = {{ModelID::ENV__SNOW_MOUNTAINS}};

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        auto input = input_manager.GetInput();
        world.Update(input, dt);
        car_camera.UpdateCameraTransform(input, local_player->vehicle_physics_comp.GetVehicleTransform(), dt);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(car_camera.camera);
            render.DrawCar(*local_player, res_manager);
            render.DrawStaticModel(env.model_comp, res_manager);
            render.DrawStaticModel(track->model_comp, res_manager);
        EndMode3D();

        EndDrawing();
    }

    res_manager.UnloadModels();
    window.Close();
}