#pragma once
#include "AudioManager.h"
#include "SpriteManager.h"
#include "IconsManager.h"
#include "LevelManager.h"
#include "TextManager.h"
#include "Random.hpp"

struct AssetManager
{
    UUIDFactory UUIDFactory;
    LevelManager Levels;
    SpriteManager Sprites;
    TextManager Text;
    AudioManager Audio;
    Random Random;

    void LoadAll();
    // IconsManager Icons;
};
