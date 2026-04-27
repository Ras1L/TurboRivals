#include "Sound/SoundManager.hpp"
#include "Sound/SoundID.hpp"
#include "raylib.h"

void SoundManager::Init(SoundID id)
{
    InitAudioDevice();
    musics = {
        {SoundID::MUS_DANGEROUS_GROUND, LoadMusicStream("assets/musics/dangerous_ground.mp3")}
    };
    currentID = id;
    current = &musics[id];
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