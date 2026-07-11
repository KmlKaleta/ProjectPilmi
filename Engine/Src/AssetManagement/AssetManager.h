#pragma once
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

    void LoadAll();
    // IconsManager Icons;
};
