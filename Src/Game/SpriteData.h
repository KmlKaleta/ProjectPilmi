#pragma once
#include <raylib.h>
#include <raymath.h>

struct SpriteData
{
    Texture2D Tex = {};
    float Scale = 1;
    Vector2 Pivot = {};

    void Render(Vector2 position)
    {
        Render(position, {0, 0, (float)Tex.width, (float)Tex.height});
    }

    void Render(Vector2 position, Rectangle texCoords, float scale = 1)
    {
        DrawTexturePro(Tex, 
            texCoords, 
            {position.x, position.y, texCoords.width * Scale * scale, texCoords.height * Scale * scale}, 
            Pivot * scale, 0, WHITE);
    }


    void Load(const char* path, float scale, Vector2 pivot)
    {
        Tex = LoadTexture(path);
        Scale = scale;
        Pivot = pivot;
    }
};