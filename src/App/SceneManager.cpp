#include "App/SceneManager.hpp"
#include "App/MenuScene.hpp"
#include "App/GameScene.hpp"

template <class... Args>
void SceneManager::Set(Scene scene, Args&&... args)
{
    if (current) {
        current -> Unload();
    }
    switch (scene)
    {
        case Scene::MENU:
            current = std::make_unique<MenuScene>();
            break;
        case Scene::GAME:
            current = std::make_unique<GameScene>(args...);
            break;
    }
    current -> Load();
}

void SceneManager::Update(float dt)
{
    current -> Update(dt);
}

void SceneManager::Render() const
{
    current -> Render();
}

void SceneManager::Reset()
{
    current -> Unload();
}