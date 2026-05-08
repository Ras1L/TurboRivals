#ifndef APP_GAME_SCENE_INFO_HPP
#define APP_GAME_SCENE_INFO_HPP

#include "Network/NetworkStatus.hpp"
#include "Sound/SoundID.hpp"
#include "Core/ModelID.hpp"

struct GameSceneInfo {
    NetworkStatus net_stat;
    SoundID       music;
    ModelID       track;
    ModelID       env;
    ModelID       my_car;
};

#endif