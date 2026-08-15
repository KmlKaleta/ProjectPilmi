//
// Created by Kamil on 28.06.2026.
//
#include "../GameSystemsUpdateArgs.h"
#include "PhysicsDebugSystem.h"

void PhysicsDebugSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<const PhysicsBoxComponent, const PhysicsBodyComponent, const
        RendererComponent>();

    for (const auto& entity : view)
    {
        const auto& body = view.get<PhysicsBodyComponent>(entity);
        const auto& box = view.get<PhysicsBoxComponent>(entity);
        const auto& renderer = view.get<RendererComponent>(entity);

        Rectangle rect = box.GetRectangle(renderer.Data.Position.GetRelative(args.ScreenBounds),
                                          renderer.Data.LocalScale);

        auto touched = RED;
        auto free = GREEN;
        DrawLineEx({rect.x, rect.y}, {rect.x + rect.width, rect.y}, 2.0f, body.Touch.Value.GetUp() ? touched : free);
        DrawLineEx({rect.x, rect.y}, {rect.x, rect.y + rect.height}, 2.0f, body.Touch.Value.GetLeft() ? touched : free);
        DrawLineEx({rect.x + rect.width, rect.y}, {rect.x + rect.width, rect.y + rect.height}, 2.0f,
                   body.Touch.Value.GetRight() ? touched : free);
        DrawLineEx({rect.x, rect.y + rect.height}, {rect.x + rect.width, rect.y + rect.height}, 2.0f,
                   body.Touch.Value.GetDown() ? touched : free);
    }
}
