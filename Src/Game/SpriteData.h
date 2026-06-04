#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>

struct SpriteData
{
    Texture2D Tex = {};
    float Scale = 1;
    Vector2 Pivot = {};
    std::vector<int> RowCounts = {1};
    int RowCountMax = 1;

    void Render(const Vector2 position, const int x = 0, const int y = 0, const bool flip = false,
                const float scale = 1, const Color tint = WHITE) const
    {
        const float width = static_cast<float>(Tex.width) / static_cast<float>(RowCountMax);
        const float height = static_cast<float>(Tex.height) / static_cast<float>(RowCounts.size());
        const float f = flip ? -1 : 1;
        Render(position, {width * static_cast<float>(x), height * static_cast<float>(y), width * f, height}, scale,
               tint);
    }

    void Render(const Vector2 position, const Rectangle texCoords, const float scale = 1,
                const Color tint = WHITE) const
    {
        DrawTexturePro(Tex,
                       texCoords,
                       {position.x, position.y, texCoords.width * Scale * scale, texCoords.height * Scale * scale},
                       Pivot * scale, 0, tint);
    }

    Rectangle GetBounds(const Vector2 position, const float scale = 1) const
    {
        const float width = static_cast<float>(Tex.width) / static_cast<float>(RowCountMax) * Scale * scale;
        const float height = static_cast<float>(Tex.height) / static_cast<float>(RowCounts.size()) * Scale * scale;

        return {
            position.x - Pivot.x * scale,
            position.y - Pivot.y * scale,
            width,
            height
        };
    }

    static SpriteData FromTextureCenter(const Texture2D& texture, const int x = 1, const int y = 1)
    {
        SpriteData spriteData{texture};
        spriteData.RowCountMax = x;
        spriteData.RowCounts.resize(y);
        for (auto& row : spriteData.RowCounts)
        {
            row = x;
        }

        spriteData.Pivot = {
            static_cast<float>(texture.width) / static_cast<float>(x * 2),
            static_cast<float>(texture.height) / static_cast<float>(y * 2)
        };
        return spriteData;
    }
};
