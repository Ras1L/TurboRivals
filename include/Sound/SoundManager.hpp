#ifndef SOUND_SOUND_MANAGER_HPP
#define SOUND_SOUND_MANAGER_HPP

#include "raylib.h"
#include "Sound/SoundID.hpp"
#include <unordered_map>

class SoundManager {
public:
    void Init(SoundID id);
    void Update();
    void Close();

    void Play(SoundID id);
    void Unload();

private:
    std::unordered_map<SoundID, Music> musics;
    SoundID currentID;
};

#endif