//
// Created by Kamil on 14.08.2026.
//
#include "PhysicsSimulationUI.h"

#include "PhysicsSimulation.h"
#include "AssetManager.h"
#include "imgui.h"
#include "SpriteEnums.h"

void PhysicsSimulationUI::Update(PhysicsSimulation& simulation, AssetManager& assets) const
{
    const size_t countPerIteration = 100;
    ImGui::Begin("Simulation");
    ImGui::Text("Entity count %llu", simulation.SimulatedEntities.size() / countPerIteration);
    LevelData& levelData = assets.Levels.CurrentLevel();
    if (ImGui::Button("-") && simulation.SimulatedEntities.size() >= countPerIteration)
    {
        for (size_t i = simulation.SimulatedEntities.size() - countPerIteration; i < simulation.SimulatedEntities.size()
             ; ++i)
        {
            levelData.Entities.DestroyEntity(simulation.SimulatedEntities[i]);
        }
        simulation.SimulatedEntities.resize(simulation.SimulatedEntities.size() - countPerIteration);
    }

    ImGui::SameLine();

    if (ImGui::Button("+"))
    {
        const size_t oldSize = simulation.SimulatedEntities.size();
        simulation.SimulatedEntities.resize(simulation.SimulatedEntities.size() + countPerIteration);
        const size_t newSize = simulation.SimulatedEntities.size();
        entt::registry& registry = levelData.Entities.Registry;
        for (size_t i = oldSize; i < newSize; ++i)
        {
            const UUID id = assets.UUIDFactory.Get();
            const entt::entity entity = levelData.Entities.CreateEntity(id);
            simulation.SimulatedEntities[i] = id;
            registry.emplace<PhysicsBodyComponent>(entity, PhysicsBodyComponent{
                                                       {}, {0, -1000.f}, Range(1.0f, 1000.0f, 90.0f)
                                                   });
            registry.emplace<MoveSpeedComponent>(entity, MoveSpeedComponent{
                                                     Range(1.0f, 1000.0f, assets.Random.GetFloat(200, 600))
                                                 });
            const uint64_t spriteId = Characters[assets.Random.GetUInt(0, Characters_Count)];
            const SpriteData sprite = assets.Sprites.FromId(spriteId);
            const RendererComponent rendererComponent{
                10, {spriteId, {assets.Random.GetFloat(-500, 500), 600, WorldAnchor::BOTTOM_CENTER}}
            };
            registry.emplace<RendererComponent>(entity, rendererComponent);
            registry.emplace<PhysicsBoxComponent>(entity, sprite.DefaultCollider);
            registry.emplace<AnimatorComponent>(entity);
        }
    }

    ImGui::End();
}
