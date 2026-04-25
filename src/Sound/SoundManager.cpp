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
    Play(currentID);
}

void SoundManager::Update()
{
    UpdateMusicStream(musics[currentID]);
}

void SoundManager::Close()
{
    Unload();
    CloseAudioDevice();
}

void SoundManager::Play(SoundID id)
{
    currentID = id;
    PlayMusicStream(musics[currentID]);
}

void SoundManager::Unload()
{
    UnloadMusicStream(musics[currentID]);
}