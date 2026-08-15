//
// Created by Kamil on 14.08.2026.
//

#ifndef SHEEP_GOES_DEVILE_PHYSICS_SIMULATION_H
#define SHEEP_GOES_DEVILE_PHYSICS_SIMULATION_H
#include "raylib.h"
#include "Systems/RenderingSystem.h"
#include "PhysicsSystem.h"
#include "UUID.hpp"
#include "Systems/AnimationSystem.h"

struct AssetManager;

struct PhysicsSimulation
{
    RenderingSystem Rendering;
    PhysicsSystem Physics;
    AnimationSystem Animation;
    Camera2D Camera;
    std::vector<UUID> SimulatedEntities;

    void Init();
    void Update(AssetManager& assetManager);
};
#endif //SHEEP_GOES_DEVILE_PHYSICS_SIMULATION_H
