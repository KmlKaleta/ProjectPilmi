//
// Created by Kamil on 28.06.2026.
//
#include "RoundSystem.h"

#include "Components.h"
#include "GameSystemsUpdateArgs.h"

void RoundSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<RoundComponent, RendererComponent, const MoveSpeedComponent>();

    for (const auto& entity : view)
    {
        const auto& tuple = view.get<RoundComponent, RendererComponent>(entity);
        auto& [round, renderer] = tuple;
        const auto& moveSpeed = view.get<MoveSpeedComponent>(entity);

        round.T += moveSpeed.Value.Get() / round.Radius.Get() * args.DeltaTime;

        renderer.Data.Move(
            round.Center.GetRelative(args.ScreenBounds) -
            Vector2{
                std::sin(round.T) * round.Radius.Get(),
                std::cos(round.T) * round.Radius.Get()
            },
            args.ScreenBounds
        );
    }
}
