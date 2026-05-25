#include "Sound/SoundManager.hpp"
#include "Sound/SoundID.hpp"
#include "raylib.h"

void SoundManager::Init()
{
    InitAudioDevice();
    musics = {
        {SoundID::MUS_DANGEROUS_GROUND, LoadMusicStream("assets/musics/dangerous_ground.mp3")}
    };
    currentID = static_cast<SoundID>(0);
    current = &musics[currentID];
    Play(currentID);
}

void SoundManager::Update()
{
    UpdateMusicStream(*current);
}

void SoundManager::Close()
{
    Unload();
    CloseAudioDevice();
}

void SoundManager::Play(SoundID id)
{
    if (currentID != id) {
        currentID = id;
        current = &musics[id];
    }
    PlayMusicStream(*current);
}

void SoundManager::Unload()
{
    UnloadMusicStream(*current);
}