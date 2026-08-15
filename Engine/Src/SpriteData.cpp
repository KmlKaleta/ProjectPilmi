//
// Created by Kamil on 09.06.2026.
//
#include "SpriteData.h"
#include "GeneratedComponents.h"
#include "raymath.h"

void SpriteData::Render(const Vector2 position, const int x, const int y, const bool flip, const float scale,
                        const Color tint) const
{
    const float width = static_cast<float>(Tex.width) / static_cast<float>(RowCountMax);
    const float height = static_cast<float>(Tex.height) / static_cast<float>(RowCounts.size());
    const float f = flip ? -1 : 1;
    Render(position, {width * static_cast<float>(x), height * static_cast<float>(y), width * f, height}, scale,
           tint);
}

void SpriteData::Render(const Vector2 position, const Rectangle texCoords, const float scale, const Color tint) const
{
    DrawTexturePro(Tex,
                   texCoords,
                   {position.x, position.y, texCoords.width * Scale * scale, texCoords.height * Scale * scale},
                   Pivot * scale, 0, tint);
}

Rectangle SpriteData::GetRenderBounds(const Vector2 position, const float scale) const
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

Rectangle SpriteData::GetBounds(const Vector2 position, const float scale) const
{
    return DefaultCollider.GetRectangle(position, scale);
}

SpriteData SpriteData::FromTextureCenter(const Texture2D& texture, const int x, const int y)
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

void to_json(JSON& j, const SpriteData& sprite)
{
    j["scale"] = sprite.Scale;
    j["pivot"] = sprite.Pivot;
    j["row_counts"] = sprite.RowCounts;
    j["row_count_max"] = sprite.RowCountMax;
    j["default_collider"] = sprite.DefaultCollider;
}

void from_json(const JSON& j, SpriteData& sprite)
{
    ReadJsonValue(sprite.Scale, j, "scale", 1.f);
    ReadJsonValue(sprite.Pivot, j, "pivot", {});
    ReadJsonValue(sprite.RowCounts, j, "row_counts", {});
    if (sprite.RowCounts.empty())
    {
        sprite.RowCounts.emplace_back(1);
    }

    ReadJsonValue(sprite.RowCountMax, j, "row_count_max", 1);
    if (sprite.RowCountMax < 1)
    {
        sprite.RowCountMax = 1;
    }
    for (auto& row : sprite.RowCounts)
    {
        row = std::clamp(row, 1, sprite.RowCountMax);
    }
    ReadJsonValue(sprite.DefaultCollider, j, "default_collider", {});
}
