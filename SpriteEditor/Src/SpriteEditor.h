//
// Created by Kamil on 27.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITE_EDITOR_H
#define SHEEP_GOES_DEVILE_SPRITE_EDITOR_H
#include "raylib.h"
#include "UUID.hpp"

struct SpriteEditor
{
    Vector2 Position = {0, 0};
    float ScaleFactor = 1.0f;
    int Row = 0;
    int Column = 0;

    UUID Ghosts[3] = {};
};
#endif //SHEEP_GOES_DEVILE_SPRITE_EDITOR_H
