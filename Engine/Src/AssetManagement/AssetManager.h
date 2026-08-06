#pragma once
#include "AudioManager.h"
#include "SpriteManager.h"
#include "IconsManager.h"
#include "LevelManager.h"
#include "TextManager.h"

struct AssetManager
{
    UUIDFactory UUIDFactory;
    LevelManager Levels;
    SpriteManager Sprites;
    TextManager Text;
    AudioManager Audio;

    void LoadAll();
    // IconsManager Icons;
};
