#include "App/SceneManager.hpp"
#include "App/ApplicationContext.hpp"
#include "App/GameScene.hpp"
#include "App/MenuScene.hpp"
#include "App/SceneSwitch.hpp"
#include "Core/Session.hpp"

SceneManager::SceneManager(ApplicationContext& context) : context(context) {}

void SceneManager::Update(float dt)
{
    const auto& ss = current -> Update(dt);
    if (ss.should_switch) {
        switch (ss.next_scene)
        {
            case Scene::GAME:
                Set<GameScene>(std::get<SessionState>(ss.next_scene_info), context.network); // Если будет больше сцен нужно убрать конкретику про GameSceneInfo
                break;
            case Scene::MENU:
                Set<MenuScene>(context.network);
                break;
        }
    }
}

void SceneManager::Render() const
{
    current -> Render();
}

void SceneManager::Reset()
{
    current -> Unload();
}