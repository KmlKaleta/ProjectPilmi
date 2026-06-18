#pragma once
#include "SpriteManager.h"
#include "IconsManager.h"
#include "LevelManager.h"


struct AssetManager
{
    SpriteManager Sprites;
    IconsManager Icons;
    LevelManager Levels;

    void LoadAll(EditorSceneOld& editor);

    void Reload();

    void SaveAll() const;
};
