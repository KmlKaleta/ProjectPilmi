#pragma once

#include <SpriteData.h>
#include <assert.h>

struct SpriteAtlas
{
    SpriteData Sprite = {};
    int SpritesX = 1;
    int SpritesY = 1;
    float SpriteWidth = 100;
    float SpriteHeight = 100;

    void Load(const char *path, float scale, Vector2 pivot, int spritesX, int spritesY)
    {
        assert(spritesX != 0 && spritesY != 0);

        Sprite.Load(path, scale, pivot);
        SpritesX = spritesX;
        SpritesY = spritesY;

        SpriteWidth = (float)Sprite.Tex.width / spritesX;
        SpriteHeight = (float)Sprite.Tex.height / spritesY;
    }

    void Render(Vector2 positon, int x, int y)
    {
        Sprite.Render(positon, Rectangle{x * SpriteWidth, y * SpriteHeight, SpriteWidth, SpriteHeight});
    }
};
