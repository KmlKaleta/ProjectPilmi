#pragma once
#include "RaylibJSON.hpp"
#include <raymath.h>
#include <vector>

struct SpriteData
{
    Texture2D Tex = {};
    float Scale = 1;
    Vector2 Pivot = {};
    std::vector<int> RowCounts = {1};
    int RowCountMax = 1;

    void Render(Vector2 position, int x = 0, int y = 0, bool flip = false,
                float scale = 1, Color tint = WHITE) const;

    void Render(Vector2 position, Rectangle texCoords, float scale = 1,
                Color tint = WHITE) const;

    Rectangle GetBounds(Vector2 position, float scale = 1) const;

    static SpriteData FromTextureCenter(const Texture2D& texture, int x = 1, int y = 1);
};

void to_json(JSON& j, const SpriteData& sprite);

void from_json(const JSON& j, SpriteData& sprite);