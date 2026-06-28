//
// Created by Kamil on 28.06.2026.
//
#include "PatrolSystem.h"

#include "Components.h"
#include "raymath.h"
#include "GameSystemsUpdateArgs.h"

void PatrolSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<RendererComponent, PatrolComponent, const MoveSpeedComponent>();

    for (const auto& entity : view)
    {
        PatrolComponent& patrolComponent = view.get<PatrolComponent>(entity);
        RendererComponent& rendererComponent = view.get<RendererComponent>(entity);
        const MoveSpeedComponent& moveSpeedComponent = view.get<MoveSpeedComponent>(entity);

        const Vector2 pos = rendererComponent.Data.Position.GetRelative(args.ScreenBounds);
        const Vector2 target = patrolComponent.Reversed ? patrolComponent.From.GetRelative(args.ScreenBounds) : patrolComponent.To.GetRelative(args.ScreenBounds);
        const float dist = moveSpeedComponent.Value.Get() * args.DeltaTime;

        if (Vector2DistanceSqr(pos, target) <= dist * dist + EPSILON)
        {
            patrolComponent.Reversed = !patrolComponent.Reversed;
            rendererComponent.Data.Move(target, args.ScreenBounds);
            continue;
        }

        const Vector2 dir = Vector2Normalize(target - pos);
        rendererComponent.Data.Move(dir, dist);
    }
}
