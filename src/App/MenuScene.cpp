#include "App/MenuScene.hpp"
#include "App/GameSceneInfo.hpp"
#include "App/SceneSwitch.hpp"
#include "Core/ModelID.hpp"
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
    (void)dt;
    static SceneSwitch ss = { false };
    if (should_switch) {
        ss.should_switch = true;
        ss.next_scene = Scene::GAME;
        ss.next_scene_info = GameSceneInfo {
            config.mode,
            static_cast<SoundID>(config.music),
            static_cast<ModelID>(config.track),
            static_cast<ModelID>(config.env),
            static_cast<ModelID>(config.car),
            config.server_ip
        };
    }
    return ss;
}

void MenuScene::Render() const
{
    rlImGuiBegin();
    ImGui::Begin(GAME_TITLE);

    ImGui::Text(GAME_TITLE);

    auto currentMode = static_cast<int>(config.mode);
    if (ImGui::Combo("Network Mode", &currentMode, modes.data(), modes.size())) {
        config.mode = static_cast<NetworkStatus>(currentMode);
    }

    ImGui::Separator();
    switch (config.mode)
    {
        case NetworkStatus::SERVER:
            DrawOwnerMenu(config);
            break;
        case NetworkStatus::CLIENT:
            DrawClientMenu(config);
            break;
        case NetworkStatus::OFFLINE:
            DrawOwnerMenu(config);
            break;
    }
    if (ImGui::Button("Start")) {
        should_switch = true;
    }

    ImGui::End();
    rlImGuiEnd();
}

void DrawOwnerMenu(GameConfig& config)
{
    ImGui::Combo("Car", &config.car, cars.data(), cars.size());
    ImGui::Combo("Track", &config.track, tracks.data(), tracks.size());
    ImGui::Combo("Environment", &config.env, environments.data(), environments.size());
    ImGui::Combo("Music", &config.music, music.data(), music.size());
}

void DrawClientMenu(GameConfig& config)
{
    ImGui::Combo("Car", &config.car, cars.data(), cars.size());
    ImGui::InputText("Connect to IP", config.server_ip, sizeof(config.server_ip));
}