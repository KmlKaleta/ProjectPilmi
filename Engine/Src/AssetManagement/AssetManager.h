#pragma once
#include "SpriteManager.h"
#include "IconsManager.h"
#include "LevelManager.h"


struct AssetManager
{
    UUIDFactory UUIDFactory;
    LevelManager Levels;

    void LoadAll();

    void SaveAll() const;

    void Reload();
    // SpriteManager Sprites;
    // IconsManager Icons;
    //
    //
    //
};
