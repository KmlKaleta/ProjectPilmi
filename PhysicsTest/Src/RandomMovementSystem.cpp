//
// Created by Kamil on 14.08.2026.
//
#include "RandomMovementSystem.h"
#include "Systems/GameSystemsUpdateArgs.h"

void RandomMovementSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<const MoveSpeedComponent, PhysicsBodyComponent>();
    for (const auto entity : view)
    {
        const auto& speed = args.Registry.get<MoveSpeedComponent>(entity).Value.Get();
        auto& body = args.Registry.get<PhysicsBodyComponent>(entity);
        if (body.Touch.Value.GetRight())
        {
            body.Velocity.x = -speed;
        }

        if (body.Touch.Value.GetLeft())
        {
            body.Velocity.x = speed;
        }

        if (body.Velocity.x == 0)
        {
            body.Velocity.x = speed;
        }

        if (body.Touch.Value.GetDown() && !body.Touch.Value.GetUp())
        {
            if (const float value = args.Assets.Random.GetValue(); value < 0.001f)
                body.Velocity.y = speed * 1.5f;
        }
    }
}
