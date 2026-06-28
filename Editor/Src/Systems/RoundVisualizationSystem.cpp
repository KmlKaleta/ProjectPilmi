//
// Created by Kamil on 28.06.2026.
//
#include "RoundVisualizationSystem.h"

#include "Components.h"
#include "Systems/GameSystemsUpdateArgs.h"

void RoundVisualizationSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<RendererComponent, const RoundComponent>();
    for (const auto& entity : view)
    {
        auto& renderer = view.get<RendererComponent>(entity);
        const auto& round = view.get<RoundComponent>(entity);
        auto centerRelative = round.Center.GetRelative(args.ScreenBounds);
        DrawCircleLinesV(centerRelative, round.Radius.Get(), BLUE);
        renderer.Data.Position.SetRelative(centerRelative, args.ScreenBounds);
    }
}
