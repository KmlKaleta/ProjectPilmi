//
// Created by Kamil on 28.06.2026.
//
#include "PatrolVisualizationSystem.h"
#include "Systems/GameSystemsUpdateArgs.h"
#include "Components.h"

void PatrolVisualizationSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<PatrolComponent>();

    for (const auto& [e, patrol] : view.each())
    {
        const Vector2 from = patrol.From.GetRelative(args.ScreenBounds);
        const Vector2 to = patrol.To.GetRelative(args.ScreenBounds);

        DrawCircleV(from, 10, GREEN);
        DrawCircleV(to, 10, RED);
        DrawLineDashed(from, to, 10, 7, DARKGREEN);
    }
}
