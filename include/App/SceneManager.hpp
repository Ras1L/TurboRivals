#ifndef APP_SCENE_MANAGER_HPP
#define APP_SCENE_MANAGER_HPP

#include "App/IScene.hpp"
#include "App/MenuScene.hpp"
#include "App/GameScene.hpp"
#include <memory>

class SceneManager {
public:
    template <class... Args>
    void Set(Scene scene, Args&&... args)
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

    void Update(float dt);
    void Render() const;
    void Reset();

private:
    std::unique_ptr<IScene> current;
};

#endif