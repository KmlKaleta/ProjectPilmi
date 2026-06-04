//
// Created by Kamil on 30.05.2026.
//

#include "IconsManager.h"
#include "raylib.h"

void IconsManager::LoadAll()
{
    Icons.push_back(SpriteData::FromTextureCenter(LoadTexture(RESOURCES_PATH "Icons/CheckMark.png")));
    const Texture2D arrowsTex = LoadTexture(RESOURCES_PATH "Icons/Arrows.png");
    SetTextureFilter(arrowsTex, TEXTURE_FILTER_POINT);
    Icons.push_back(SpriteData::FromTextureCenter(arrowsTex, 4, 1));

    Ids[StringToHash("CheckMark")] = 0;
    Ids[StringToHash("Arrows")] = 1;
}

void IconsManager::Reload()
{
    for (const auto& icon : Icons)
    {
        UnloadTexture(icon.Tex);
    }
    *this = IconsManager();
    LoadAll();
}
