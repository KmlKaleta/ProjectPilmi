//
// Created by Kamil on 26.05.2026.
//
#include "Renderer.h"
#include "SpriteManager.h"
#include "raymath.h"

void Renderer::Render(const WorldScreenBounds& screenBounds, const SpriteManager& sprites) const
{
    const SpriteData sprite = sprites.FromId(Sprite);
    sprite.Render(Position.GetRelative(screenBounds), TexX, TexY, Flip, LocalScale);
}

void Renderer::Render(const SpriteManager& sprites, const Vector2& positionOverride) const
{
    const SpriteData sprite = sprites.FromId(Sprite);
    sprite.Render(positionOverride, TexX, TexY, Flip, LocalScale);
}

Rectangle Renderer::GetBounds(const WorldScreenBounds& screenBounds, const SpriteManager& sprites) const
{
    const SpriteData sprite = sprites.FromId(Sprite);
    return sprite.GetRenderBounds(Position.GetRelative(screenBounds), LocalScale);
}

void Renderer::Move(const Vector2 direction, const float speed)
{
    Position.Value += direction * speed;

    if (direction.x < 0)
    {
        Flip = true;
    }

    if (direction.x > 0)
    {
        Flip = false;
    }
}

void Renderer::Move(const Vector2 position, const WorldScreenBounds& screenBounds)
{
    const Vector2 lastPosition = Position.GetRelative(screenBounds);
    const Vector2 newPosition = Position.ToRelative(position, screenBounds);
    Flip = newPosition.x < lastPosition.x;
    Position.Value = newPosition;
}

void Renderer::ClampTex(const SpriteManager& sprites)
{
    TexY = std::clamp(TexY, 0, static_cast<int>(sprites.FromId(Sprite).RowCounts.size()) - 1);
    TexX = std::clamp(TexX, 0, sprites.FromId(Sprite).RowCounts[TexY] - 1);
}

void to_json(JSON& j, const Renderer& renderer)
{
    j["sprite"] = renderer.Sprite;
    j["position"] = renderer.Position;
    j["scale"] = renderer.LocalScale;
    j["flip"] = renderer.Flip;
    j["tex_x"] = renderer.TexX;
    j["tex_y"] = renderer.TexY;
}

void from_json(const JSON& j, Renderer& renderer)
{
    ReadJsonValue(renderer.Sprite, j, "sprite", {});
    ReadJsonValue(renderer.Position, j, "position", {});
    ReadJsonValue(renderer.LocalScale, j, "scale", 1.f);
    ReadJsonValue(renderer.Flip, j, "flip", false);
    ReadJsonValue(renderer.TexX, j, "tex_x", 0);
    ReadJsonValue(renderer.TexY, j, "tex_y", 0);
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
