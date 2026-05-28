#ifndef APP_SCENE_SWITCH_HPP
#define APP_SCENE_SWITCH_HPP

#include "Core/Session.hpp"
#include <variant>

enum class Scene {
    MENU,
    GAME
};

struct SceneSwitch {
    bool  should_switch = false;
    Scene next_scene;
    std::variant<SessionState> next_scene_info;
};

#endif