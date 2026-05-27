#include "App/MenuScene.hpp"
#include "App/SceneSwitch.hpp"
#include "Core/ModelID.hpp"
#include "Core/Session.hpp"
#include "Network/MessageProcessor.hpp"
#include "Network/NetworkManager.hpp"
#include "Network/NetworkMessage.hpp"
#include "Network/NetworkRole.hpp"
#include "Network/NetworkStatus.hpp"
#include "rlImGui.h"
#include "imgui.h"
#include <array>

constexpr const char* GAME_TITLE = "TurboRivals";

static constexpr std::array<const char*, 3> modes = {
    "Offline",
    "Client",
    "Server"
};

static constexpr std::array<const char*, 1> tracks = {
    "Circuit1"
};

static constexpr std::array<const char*, 1> music = {
    "Dangerous Ground"
};

static constexpr std::array<const char*, 1> environments = {
    "Mountains"
};

static constexpr std::array<const char*, 3> cars = {
    "Porsche 911 Carrera 993",
    "Dodge Charger R/T 1969",
    "Horai BX300 1996"
};

MenuScene::MenuScene(NetworkManager& network) : network(network) {}

void MenuScene::Load()
{
    rlImGuiSetup(false);
}

void MenuScene::Unload()
{
    rlImGuiShutdown();
}

SceneSwitch MenuScene::Update(float dt)
{
    static SceneSwitch  ss = { false };
    static SessionState session;

    if (mode == MenuMode::LOBBY) {
        NetworkMessage msg;
        MsgQueue       queue;

        switch (config.mode) {
            case NetworkRole::CLIENT: msg = MessageProcessor::Serialize(static_cast<ModelID>(config.car)); break;
            case NetworkRole::SERVER: msg = MessageProcessor::Serialize(session); break;
            default: break;
        }
        queue   = network.Update(msg, dt);
        session = MessageProcessor::ApplyChanges(session, queue);
    }

    if (should_switch) {
        if (config.mode == NetworkRole::OFFLINE) {
            session = {
                static_cast<ModelID>(config.track + cars.size() + environments.size()),
                static_cast<ModelID>(config.env + cars.size()),
                {{ 0, static_cast<ModelID>(config.car), {0.f, 2.f, 0.f} }}
            };
        }

        ss.should_switch = true;
        ss.next_scene = next_scene;
        ss.next_scene_info = session;
    }
    return ss;
}

void MenuScene::Render() const
{
    switch (mode)
    {
        case MenuMode::MAIN:
            DrawMain();
            break;

        case MenuMode::LOBBY:
            DrawLobby();
            break;
    }
}

void MenuScene::DrawMain() const
{
    rlImGuiBegin();
    ImGui::Begin(GAME_TITLE);

    ImGui::Text(GAME_TITLE);

    auto currentMode = static_cast<int>(config.mode);
    if (ImGui::Combo("Network Mode", &currentMode, modes.data(), modes.size())) {
        config.mode = static_cast<NetworkRole>(currentMode);
    }

    ImGui::Separator();
    switch (config.mode)
    {
        case NetworkRole::SERVER:
            DrawOwnerMenu(config);
            break;
        case NetworkRole::CLIENT:
            DrawClientMenu(config);
            break;
        case NetworkRole::OFFLINE:
            DrawOwnerMenu(config);
            break;
    }
    if (ImGui::Button("Start")) {
        if (config.mode == NetworkRole::OFFLINE) {
            SwitchToGame();
        } else {
            SwitchToLobby();
        }
    }

    ImGui::End();
    rlImGuiEnd();
}

void MenuScene::DrawLobby() const
{
    rlImGuiBegin();
    ImGui::Begin(GAME_TITLE);

    ImGui::Text(GAME_TITLE);
    ImGui::Text("Waiting for players...");
    if (ImGui::Button("Start")) {
        SwitchToGame();
    }

    ImGui::End();
    rlImGuiEnd();
}

void MenuScene::DrawOwnerMenu(GameConfig& config) const
{
    ImGui::Combo("Car", &config.car, cars.data(), cars.size());
    ImGui::Combo("Track", &config.track, tracks.data(), tracks.size());
    ImGui::Combo("Environment", &config.env, environments.data(), environments.size());
    ImGui::Combo("Music", &config.music, music.data(), music.size());
}

void MenuScene::DrawClientMenu(GameConfig& config) const
{
    ImGui::Combo("Car", &config.car, cars.data(), cars.size());
    ImGui::InputText("Connect to IP", config.server_ip, sizeof(config.server_ip));
}

void MenuScene::SwitchToLobby() const
{
    mode = MenuMode::LOBBY;
    network.Init(config.mode);
    network.Connect(config.server_ip);
}

void MenuScene::SwitchToGame() const
{
    should_switch = true;
    next_scene = Scene::GAME;
    network.SetStatus(NetworkStatus::PLAYING);
}