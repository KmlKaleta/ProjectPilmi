//
// Created by Kamil on 28.06.2026.
//
#include "EditorLevel.h"
#include "AssetManager.h"
#include "Systems/GameSystemsUpdateArgs.h"

void EditorLevel::Init()
{
    Camera.target = {0, 0};
    Camera.rotation = 0;
    Camera.zoom = 1;
}

void EditorLevel::Update(AssetManager& assetManager)
{
    ClearBackground(ORANGE);

    Camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    BeginMode2D(Camera);

    LevelData& level = assetManager.Levels.CurrentLevel();

    const WorldScreenBounds bounds{Camera};
    GameSystemsUpdateArgs args{
        level.Entities.Registry,
        GetFrameTime(),
        assetManager,
        bounds
    };

    Systems.Update(args);
    EndMode2D();
}