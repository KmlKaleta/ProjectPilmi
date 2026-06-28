#pragma once
#include "Fields/WorldPosition.hpp"
#include "UUID.hpp"

struct SpriteManager;

struct Renderer
{
    UUID Sprite{};
    WorldPosition Position = {};
    float LocalScale = 1;
    bool Flip = false;
    int TexX = 0;
    int TexY = 0;

    void Render(const WorldScreenBounds& screenBounds, const SpriteManager& sprites) const;

    void Render(const SpriteManager& sprites, const Vector2& positionOverride) const;

    Rectangle GetBounds(const WorldScreenBounds& screenBounds, const SpriteManager& sprites) const;

    void Move(Vector2 direction, float speed);

    void Move(Vector2 position, const WorldScreenBounds& screenBounds);

    void ClampTex(const SpriteManager& sprites);
};

void to_json(JSON& j, const Renderer& renderer);

void from_json(const JSON& j, Renderer& renderer);
