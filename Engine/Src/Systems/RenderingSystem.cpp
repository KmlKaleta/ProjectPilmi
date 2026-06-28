//
// Created by Kamil on 28.06.2026.
//
#include "RenderingSystem.h"

#include "GameSystemsUpdateArgs.h"
#include "../components.h"

void RenderingSystem::Update(GameSystemsUpdateArgs& args)
{
    const auto& view = args.Registry.view<const RendererComponent>();

    Order.assign(view.begin(), view.end());
    std::sort(Order.begin(), Order.end(), [&](const auto& a, const auto& b)
    {
        return view.get<RendererComponent>(a).LayerOrder < view.get<RendererComponent>(b).LayerOrder;
    });

    for (const auto& entity : Order)
    {
        const RendererComponent& rendererComponent = view.get<RendererComponent>(entity);
        rendererComponent.Data.Render(args.ScreenBounds, args.Assets.Sprites);
    }
}
