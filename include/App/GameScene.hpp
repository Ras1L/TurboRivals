#ifndef APP_GAME_SCENE_HPP
#define APP_GAME_SCENE_HPP

#include "App/IScene.hpp"
#include "App/GameSceneInfo.hpp"
#include "App/SceneSwitch.hpp"
#include "Core/Environment.hpp"
#include "Core/GameWorld.hpp"
#include "Core/Session.hpp"
#include "Network/NetworkManager.hpp"
#include "Render/CarCamera.hpp"
#include "Render/RenderSystem.hpp"
#include "Render/ResourceManager.hpp"
#include "Sound/SoundManager.hpp"
#include "UI/InputManager.hpp"
#include <vector>

class GameScene final : public IScene {
public:
    GameScene() = default; // на время, может определю как нибудь
    GameScene(const GameSceneInfo& info);

    void Load() override;
    SceneSwitch Update(float dt) override;
    void Render() const override;
    void Unload() override;

private:
    GameSceneInfo   info;
    SessionState    session;

    InputManager    input;
    CarCamera       camera;
    NetworkManager  network;
    ResourceManager resources;
    RenderSystem    render;
    GameWorld       world;
    SoundManager    sound;

    const Car*              local_car;
    std::vector<const Car*> cars;
    const Track*            track;
    const Environment*      env;
};

#endif