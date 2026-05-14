#include "App/SceneManager.hpp"
#include "App/GameSceneInfo.hpp"
#include "App/SceneSwitch.hpp"

void SceneManager::Update(float dt)
{
    const auto& ss = current -> Update(dt);
    if (ss.should_switch) {
        switch (ss.next_scene)
        {
            case Scene::GAME:
                Set(ss.next_scene, std::get<GameSceneInfo>(ss.next_scene_info)); // Если будет больше сцен нужно убрать конкретику про GameSceneInfo
                break;
            case Scene::MENU:
                Set(ss.next_scene);
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