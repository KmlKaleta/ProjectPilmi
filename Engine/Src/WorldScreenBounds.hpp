//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_WORLD_SCREEN_BOUNDS_HPP
#define SHEEP_GOES_DEVILE_WORLD_SCREEN_BOUNDS_HPP
#include "raylib.h"

struct WorldScreenBounds
{
    Vector2 Min;
    Vector2 Max;

    WorldScreenBounds(const Camera2D& camera) : Min(GetScreenToWorld2D({0, 0}, camera)),
                                         Max(GetScreenToWorld2D({
                                                                    static_cast<float>(GetScreenWidth()),
                                                                    static_cast<float>(GetScreenHeight())
                                                                }, camera))
    {
    }
};

#endif //SHEEP_GOES_DEVILE_WORLD_SCREEN_BOUNDS_HPP
