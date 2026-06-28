//
// Created by Kamil on 28.06.2026.
//
#include "ParallaxSystem.h"

#include "Components.h"
#include "SpriteData.h"
#include "SpriteManager.h"
#include "GameSystemsUpdateArgs.h"

void ParallaxSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<const ParallaxComponent, RendererComponent>();
    for (const auto& entity : view)
    {
        const auto& parallax = view.get<ParallaxComponent>(entity);
        auto& renderer = view.get<RendererComponent>(entity);

        SpriteData sprite = args.Assets.Sprites.FromId(renderer.Data.Sprite);
        const auto texWidth = static_cast<float>(sprite.Tex.width);
        const auto texHeight = static_cast<float>(sprite.Tex.height);
        const auto doubleScreenWidth = static_cast<float>(GetScreenWidth()) * 2.0f;
        const auto doubleScreenHeight = static_cast<float>(GetScreenHeight()) * 2.0f;

        const float x = std::ceil(doubleScreenWidth / texWidth);
        const float y = std::ceil(doubleScreenHeight / texHeight);

        renderer.Data.LocalScale = std::max(x, y);
    }
}
