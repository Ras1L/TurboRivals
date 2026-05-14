#ifndef APP_GAME_SCENE_INFO_HPP
#define APP_GAME_SCENE_INFO_HPP

#include "Network/NetworkStatus.hpp"
#include "Sound/SoundID.hpp"
#include "Core/ModelID.hpp"
#include <string>

struct GameSceneInfo {
    NetworkStatus net_stat = NetworkStatus::OFFLINE;
    SoundID       music    = SoundID::MUS_NONE;
    ModelID       track    = ModelID::NONE;
    ModelID       env      = ModelID::NONE;
    ModelID       car      = ModelID::NONE;
    std::string   server_ip = "127.0.0.1";
};

#endif