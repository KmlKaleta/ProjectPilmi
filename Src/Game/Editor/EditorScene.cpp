//
// Created by Kamil on 26.05.2026.
//

#include "EditorScene.h"
#include "AssetManagement/AssetManager.h"
#include "raygui.h"
#include "EditorSceneWrapper.h"

void EditorScene::Update(AssetManager& assetManager)
{
    const Vector2 mouseScreenPos = GetMousePosition();
    const Vector2 mousePos = GetScreenToWorld2D(mouseScreenPos, Camera);

    BeginMode2D(Camera);

    LevelData& levelData = assetManager.Levels.Data[CurrentLevel];
    for (size_t i = 0; i < levelData.size(); ++i)
    {
        const Renderer& renderer = levelData.GetRenderer(i);
        renderer.Render(assetManager.Sprites);
    }

    switch (State)
    {
        case EDITOR_PALETTE:
            Palette.Update(mousePos, CanInteract, levelData, assetManager.Sprites);
            break;
        case EDITOR_RENDERERS:
        case EDITOR_COMPONENTS:
            RenderersEditor.Update(mousePos, CanInteract, levelData, assetManager.Sprites);
            break;
        default:
            break;
    }
    EndMode2D();
}

void EditorScene::Reset()
{
    *this = EditorScene();
    Init();
}

void EditorScene::Init()
{
    Camera.target = {0, 0};
    Camera.rotation = 0;
    Camera.zoom = 1;

    const auto screenWidth = static_cast<float>(GetScreenWidth());
    const auto screenHeight = static_cast<float>(GetScreenHeight());
    Camera.offset = {screenWidth / 2, screenHeight / 2};
}
