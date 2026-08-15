#pragma once
#include <vector>
#include "Components.h"

struct SpriteData
{
    Texture2D Tex = {};
    float Scale = 1;
    Vector2 Pivot = {};
    std::vector<int> RowCounts = {1};
    int RowCountMax = 1;
    PhysicsBoxComponent DefaultCollider;

    SpriteData(SpriteData&&) = default;

    SpriteData() = default;

    SpriteData(const SpriteData&) = default;

    void Render(Vector2 position, int x = 0, int y = 0, bool flip = false,
                float scale = 1, Color tint = WHITE) const;

    void Render(Vector2 position, Rectangle texCoords, float scale = 1,
                Color tint = WHITE) const;

    Rectangle GetRenderBounds(Vector2 position, float scale = 1) const;

    Rectangle GetBounds(Vector2 position, float scale = 1) const;

    static SpriteData FromTextureCenter(const Texture2D& texture, int x = 1, int y = 1);

    SpriteData& operator=(const SpriteData&) = default;
    SpriteData& operator=(SpriteData&&) = default;
};

void to_json(JSON& j, const SpriteData& sprite);

void from_json(const JSON& j, SpriteData& sprite);