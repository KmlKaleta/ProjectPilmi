//
// Created by Kamil on 09.07.2026.
//
#include "ScaleToScreenSystem.h"
#include "GameSystemsUpdateArgs.h"

void ScaleToScreenSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<ScaleToScreenTag, RendererComponent>();

    for (const auto& entity : view)
    {
        auto& renderer = view.get<RendererComponent>(entity);
        const auto width = static_cast<float>(GetScreenWidth());
        const auto height = static_cast<float>(GetScreenHeight());
        const Texture2D tex = args.Assets.Sprites.FromId(renderer.Data.Sprite).Tex;

        if (!IsTextureValid(tex))
            continue;

        renderer.Data.LocalScale = std::min(width / static_cast<float>(tex.width),
            height / static_cast<float>(tex.height));
    }
}
