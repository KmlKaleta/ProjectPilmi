#pragma once
#include "AssetManagement/AssetManager.h"
#include "Editor/EditorScene.h"
#include "EditorUI.h"
#include "ImGuiManager.h"

struct GameplayUpdateArgs
{
    AssetManager AssetManager;
    EditorScene EditorScene;
    EditorUi EditorUi;
    ImGuiManager ImGuiManager;

    void Init()
    {
        EditorScene.Init();
        ImGuiManager.Init(AssetManager);
        EditorUi.Init();
    }
};

struct Gameplay
{
    static bool Init(GameplayUpdateArgs &args);

    static bool Update(GameplayUpdateArgs &args);

    static bool Close(GameplayUpdateArgs &args);
};
