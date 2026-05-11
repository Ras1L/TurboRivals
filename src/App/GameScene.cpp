#include "App/GameScene.hpp"
#include "Core/GameWorldInitData.hpp"
#include "Core/ModelID.hpp"
#include "raylib.h"

GameScene::GameScene(const GameSceneInfo& info) : info(info) {}

void GameScene::Load()
{
    network.Init(info.net_stat);
    const auto& session = network.GetSessionState(); // Получать координаты спавна и прочее

    resources.InitModels();
    GameWorldInitData init_data;
    init_data.track_col_mesh = resources.GetCollisionMeshDataByID(session.track);

    world.Init(session, init_data); // Учитывать то что для клиента данные приходят из сети (session), а сервер в меню что-то выбрал и использует (info)
    cars  = world.GetCars();
    track = world.GetTrack();
    env   = world.GetEnvironment();

    sound.Init(info.music);
}

void GameScene::Update(float dt)
{
    network.Update(dt);
    world.Update(input.GetInput().vehicle, dt);
    camera.Update(input.GetInput().camera, local_car -> vehicle_physics_comp.GetVehicleTransform(), dt); // Указать камере следить за конкретным игроком
    sound.Update();
}

void GameScene::Render() const
{
    BeginMode3D(camera.m_camera);
    render.DrawCars(cars, resources);
    render.DrawStaticModel(track -> model_comp, resources);
    render.DrawStaticModel(env -> model_comp, resources);
    EndMode3D();
}

void GameScene::Unload()
{
    sound.Close();
    resources.UnloadModels();
    network.Deinit();
}