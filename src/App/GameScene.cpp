#include "App/GameScene.hpp"
#include "App/SceneSwitch.hpp"
#include "App/SessionBuilder.hpp"
#include "Core/GameWorldInitData.hpp"
#include "raylib.h"
#include <vector>

GameScene::GameScene(const GameSceneInfo& info) : info(info) {}

void GameScene::Load()
{
    network.Init(info.net_stat);
    network.Connect(info.server_ip); // если клиент то он там подключиться
    auto msg = network.WaitForStart(20.f); // TODO: сделать чтоб сервер через ENet::PollEvents несколько раз посылал broadcast-ом SesstionState
    if (msg.has_value()) {
        session = SessionBuilder::Deserialize(msg.value());
    } else {
        should_switch = true;
        return;
    }

    resources.InitModels();
    GameWorldInitData init_data;
    init_data.track_col_mesh = resources.GetCollisionMeshDataByID(session.track);

    world.Init(session, init_data); // Учитывать то что для клиента данные приходят из сети (session), а сервер в меню что-то выбрал и использует (info)
    {
        auto all_cars = world.GetCars();
        local_car = all_cars.front();
        cars.assign(all_cars.cbegin() + 1, all_cars.cend());
    }
    track = world.GetTrack();
    env   = world.GetEnvironment();

    sound.Init(info.music);
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
    world.Update(input.GetInput().vehicle, dt);
    camera.Update(input.GetInput().camera, local_car -> vehicle_physics_comp.GetVehicleTransform(), dt); // Указать камере следить за конкретным игроком
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