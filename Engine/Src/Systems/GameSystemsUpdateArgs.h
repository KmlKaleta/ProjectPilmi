//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_GAME_SYSTEMS_UPDATE_ARGS_H
#define SHEEP_GOES_DEVILE_GAME_SYSTEMS_UPDATE_ARGS_H
#include "WorldScreenBounds.hpp"
#include "AssetManager.h"

struct GameSystemsUpdateArgs
{
    entt::registry& Registry;
    float DeltaTime;
    const AssetManager& Assets;
    const WorldScreenBounds& ScreenBounds;
};

#endif //SHEEP_GOES_DEVILE_GAME_SYSTEMS_UPDATE_ARGS_H
