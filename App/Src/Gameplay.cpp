//
// Created by Kamil on 28.06.2026.
//
#include "Gameplay.h"

#include "AssetManager.h"
#include "Systems/GameSystemsUpdateArgs.h"

void Gameplay::Init()
{
    Camera.target = {0, 0};
    Camera.rotation = 0;
    Camera.zoom = 1;
}

// ReSharper disable once CppDFAConstantFunctionResult
void Gameplay::Update(AssetManager& assetManager)
{
    ClearBackground(BLACK);

    Camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    BeginMode2D(Camera);

    GameSystemsUpdateArgs args(assetManager, Camera, true, true);

    Systems.Update(args);

    if (WindowShouldClose())
    {
        return;
    }

    EndMode2D();
}
