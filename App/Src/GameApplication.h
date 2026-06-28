//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_GAME_APPLICATION_H
#define SHEEP_GOES_DEVILE_GAME_APPLICATION_H
#include "AssetManager.h"
#include "Gameplay.h"

struct GameApplication
{
    AssetManager Assets;
    Gameplay Gameplay;

    bool Init();

    bool Update();

    void Close();
};
#endif //SHEEP_GOES_DEVILE_GAME_APPLICATION_H
