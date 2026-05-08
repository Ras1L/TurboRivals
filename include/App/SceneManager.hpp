#ifndef APP_SCENE_MANAGER_HPP
#define APP_SCENE_MANAGER_HPP

#include "App/GameSceneInfo.hpp"
#include "App/IScene.hpp"
#include <memory>

enum class Scene {
    MENU,
    GAME
};

class SceneManager {
public:
    template <class ...Args>
    void Set(Scene scene, Args&&... args);

    void Update(float dt); // TODO: возможно здесь надо будет сделать чтоб сцены посылали сигнал, что они закроются, и сцена менялась там на ходу
    void Render() const;
    void Reset();

    // может сделаю этот метод гибким потом
    GameSceneInfo GetInfo();

private:
    std::unique_ptr<IScene> current;
};

#endif