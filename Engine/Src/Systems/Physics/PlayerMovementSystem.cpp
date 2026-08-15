//
// Created by Kamil on 07.08.2026.
//
#include "PlayerMovementSystem.h"
#include "../GameSystemsUpdateArgs.h"

#include "raylib.h"

void PlayerMovementSystem::Update(GameSystemsUpdateArgs& args) const
{
    float xVel = 0;

    if (IsKeyDown(KEY_LEFT))
    {
        xVel -= 1;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        xVel += 1;
    }

    const auto& view = args.Registry.view<const PlayerControllableTag, PhysicsBodyComponent, const
        MoveSpeedComponent>();

    for (const auto entity : view)
    {
        auto& body = view.get<PhysicsBodyComponent>(entity);
        auto& moveSpeed = view.get<MoveSpeedComponent>(entity);

        body.Velocity.x = xVel * moveSpeed.Value.Get();
        if (IsKeyPressed(KEY_SPACE))
            if (body.Touch.Value.GetDown() && !body.Touch.Value.GetUp())
            {
                body.Velocity.y = 1000;
            }
    }
}
