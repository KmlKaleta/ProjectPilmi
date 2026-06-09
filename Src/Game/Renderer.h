#pragma once
#include "RaylibJSON.hpp"

struct SpriteManager;

struct Renderer
{
    uint64_t Sprite = 0;
    Vector2 Position = {};
    float LocalScale = 1;
    bool Flip = false;
    int TexX = 0;
    int TexY = 0;

    void Render(const SpriteManager& assetManager) const;

    Rectangle GetBounds(const SpriteManager& assetManager) const;

    void ClampTex(const SpriteManager& spriteManager);
};

void to_json(JSON& j, const Renderer& renderer);

void from_json(const JSON& j, Renderer& renderer);