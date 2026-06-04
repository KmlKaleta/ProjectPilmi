#pragma once
#include "SpriteManager.h"
#include "IconsManager.h"


struct AssetManager
{
    SpriteManager Sprites;
    IconsManager Icons;

    void LoadAll();

    void Reload();

    void SaveAll() const;

    //void Delete(size_t index);
};
