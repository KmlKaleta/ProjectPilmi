//
// Created by Kamil on 28.06.2026.
//
#include "../GameSystemsUpdateArgs.h"
#include "VelocitySystem.h"

void VelocitySystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<PhysicsBodyComponent, RendererComponent>();
    for (const auto& entity : view)
    {
        auto& physicsBody = view.get<PhysicsBodyComponent>(entity);
        auto& renderer = view.get<RendererComponent>(entity);
        renderer.Data.Move(physicsBody.Velocity, args.DeltaTime);
        physicsBody.Velocity.y -= 20.0f * args.DeltaTime * physicsBody.Mass.Get();
        physicsBody.Velocity.y = std::max(physicsBody.Velocity.y, -90000.f);
        //physicsBody.Velocity.x *= 0.95f;
    }
}
