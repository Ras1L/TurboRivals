#ifndef APP_SCENE_SWITCH_HPP
#define APP_SCENE_SWITCH_HPP

#include "App/GameSceneInfo.hpp"
#include <variant>

enum class Scene {
    MENU,
    GAME
};

struct SceneSwitch {
    bool  should_switch;
    Scene next_scene;
    std::variant<GameSceneInfo> next_scene_info;
};

#endif