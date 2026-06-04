//
// Created by Kamil on 26.05.2026.
//
#include "SpriteManager.h"
#include "Renderer.h"

void Renderer::Render(const SpriteManager& spritesManager) const
{
    const SpriteData sprite = spritesManager.FromId(Sprite);
    sprite.Render(Position, TexX, TexY, Flip, LocalScale);
}

Rectangle Renderer::GetBounds(const SpriteManager& spritesManager) const
{
    const SpriteData sprite = spritesManager.FromId(Sprite);
    return sprite.GetBounds(Position, LocalScale);
}


// void Render(const Vector2 position, const int x = 0, const int y = 0, const bool flip = false,
//                 const float scale = 1, const Color tint = WHITE) const
// {
//     const float width = static_cast<float>(Tex.width) / static_cast<float>(RowCountMax);
//     const float height = static_cast<float>(Tex.height) / static_cast<float>(RowCounts.size());
//     const float f = flip ? -1 : 1;
//     Render(position, {width * static_cast<float>(x), height * static_cast<float>(y), width * f, height}, scale,
//            tint);
// }
//
// void Render(const Vector2 position, const Rectangle texCoords, const float scale = 1,
//             const Color tint = WHITE) const
// {
//     DrawTexturePro(Tex,
//                    texCoords,
//                    {position.x, position.y, texCoords.width * Scale * scale, texCoords.height * Scale * scale},
//                    Pivot * scale, 0, tint);
// }
