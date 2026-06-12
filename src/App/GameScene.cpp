#include "App/GameScene.hpp"
#include "App/SceneSwitch.hpp"
#include "Core/GameWorldInitData.hpp"
#include "Core/Session.hpp"
#include "Network/NetworkManager.hpp"
#include "Network/NetworkMessage.hpp"
#include "Network/MessageProcessor.hpp"
#include "Network/NetworkRole.hpp"
#include <iostream>

GameScene::GameScene(const SessionState& session, NetworkManager& network) : session(session), network(network) {}

void GameScene::Load()
{
    resources.InitModels();
    GameWorldInitData init_data;
    init_data.track_col_mesh = resources.GetCollisionMeshDataByID(session.track);

    for (id_type i = 0; i < MAX_PLAYERS; ++i) {
        auto& info                  = session.players[i];
        auto& runtime_player = session_runtime.players[i];

        runtime_player.info       = info;
        runtime_player.trans.pos  = info.spawn; // pos - динамическая переменная, а spawn - один и тот же
    }
    session_runtime.my_id = session.my_id;

    std::cout << "->>>>>>>>>>>>" << int(session.my_id) << '\n';

    world.Init(session, init_data);
    cars      = world.GetCars();
    local_car = world.GetLocalCar();
    track     = world.GetTrack();
    env       = world.GetEnvironment();

    sound.Init();

    my_role = network.GetRole();
}

SceneSwitch GameScene::Update(float dt)
{
    static SceneSwitch ss;
    if (should_switch) {
        ss.should_switch = true;
        ss.next_scene = Scene::MENU;
        return ss;
    }

    my_input = input_manager.GetInput();

    if (my_role != NetworkRole::CLIENT) {
        session_runtime.players[session_runtime.my_id].input = my_input.vehicle;
    }

    if (my_role != NetworkRole::OFFLINE) {
        NetworkMessage msg;
        MsgQueue       queue;
        switch (my_role) {
            case NetworkRole::CLIENT: msg = MessageProcessor::Serialize(my_input.vehicle); break;
            case NetworkRole::SERVER: msg = MessageProcessor::Serialize(session_runtime); break;
            default: break;
        }
        queue = network.Update(msg, dt);
        MessageProcessor::ApplyChanges(session_runtime, queue);
    }

    if (my_role == NetworkRole::CLIENT) {
        world.ApplyShapshot(session_runtime);
    }
    world.Update(session_runtime, dt);
    camera.Update(my_input.camera, local_car -> vehicle_physics_comp.GetVehicleTransform(), dt); // Указать камере следить за конкретным игроком
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