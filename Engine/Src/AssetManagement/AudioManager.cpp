//
// Created by Kamil on 13.07.2026.
//
#include "AudioManager.h"


void AudioManager::LoadAll()
{
    InitAudioDevice();
    SetMasterVolume(0.15);
    Hover = LoadSound(RESOURCES_PATH "Sounds/UI/ButtonHover.ogg");
    Click = LoadSound(RESOURCES_PATH "Sounds/UI/ButtonClick.ogg");
    MenuMusic = LoadMusicStream(RESOURCES_PATH "Sounds/Music/bonus.ogg");
    MenuMusic.looping = true;
    PlayMusicStream(MenuMusic);
}
