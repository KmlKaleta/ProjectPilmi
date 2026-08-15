//
// Created by Kamil on 14.08.2026.
//
#include "PhysicsSimulation.h"

#include "Systems/GameSystemsUpdateArgs.h"

void PhysicsSimulation::Init()
{
    Camera.target = {0, 0};
    Camera.rotation = 0;
    Camera.zoom = 1;
}

void PhysicsSimulation::Update(AssetManager& assetManager)
{
    ClearBackground(BLACK);

    Camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    BeginMode2D(Camera);

    GameSystemsUpdateArgs args(assetManager, Camera, true, true);

    Physics.Update(args);
    Rendering.Update(args);
    Animation.Update(args);
    if (WindowShouldClose())
    {
        return;
    }

    EndMode2D();
}
