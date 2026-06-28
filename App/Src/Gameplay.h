//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_GAMEPLAY_H
#define SHEEP_GOES_DEVILE_GAMEPLAY_H
#include <raylib.h>
#include "Systems/GameSystems.h"

struct AssetManager;

struct Gameplay
{
    Camera2D Camera{};
    GameSystems Systems;

    void Init();

    void Update(AssetManager& assetManager);
};

#endif //SHEEP_GOES_DEVILE_GAMEPLAY_H
