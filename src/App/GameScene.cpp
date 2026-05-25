#include "App/GameScene.hpp"
#include "App/SceneSwitch.hpp"
#include "Core/GameWorldInitData.hpp"
#include "Core/Session.hpp"
#include "Network/NetworkManager.hpp"

GameScene::GameScene(const SessionState& session, NetworkManager& network) : session(session), network(network) {}

void GameScene::Load()
{
    resources.InitModels();
    GameWorldInitData init_data;
    init_data.track_col_mesh = resources.GetCollisionMeshDataByID(session.track);

    world.Init(session, init_data);
    cars      = world.GetCars();
    local_car = cars.front();
    track     = world.GetTrack();
    env       = world.GetEnvironment();

    sound.Init();
}

SceneSwitch GameScene::Update(float dt)
{
    static SceneSwitch ss = {false};
    if (should_switch) {
        ss.should_switch = true;
        ss.next_scene = Scene::MENU;
        return ss;
    }

    network.Update(dt);
    input = input_manager.GetInput();
    world.Update(input.vehicle, dt);
    camera.Update(input.camera, local_car -> vehicle_physics_comp.GetVehicleTransform(), dt); // Указать камере следить за конкретным игроком
    sound.Update();

    return ss;
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