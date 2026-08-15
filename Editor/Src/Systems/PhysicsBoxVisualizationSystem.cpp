//
// Created by Kamil on 28.06.2026.
//
#include "PhysicsBoxVisualizationSystem.h"
#include "Systems/GameSystemsUpdateArgs.h"
#include "Components.h"

void PhysicsBoxVisualizationSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<const PhysicsBoxComponent, const RendererComponent>();

    for (const auto& [e, box, renderer] : view.each())
    {
        Vector2 pos = renderer.Data.Position.GetRelative(args.ScreenBounds);
        DrawRectangleLinesEx(box.GetRectangle(pos, renderer.Data.LocalScale), 2.f, DARKGREEN);
    }
}
