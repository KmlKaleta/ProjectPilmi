#pragma once
#include "SpriteManager.h"
#include "IconsManager.h"
#include "LevelManager.h"

struct AssetManager
{
    UUIDFactory UUIDFactory;
    LevelManager Levels;
    SpriteManager Sprites;

    void LoadAll();
    // IconsManager Icons;
};
