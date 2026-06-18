#pragma once
#include "AssetManagement/AssetManager.h"
#include "Editor/EditorSceneOld.h"
#include "EditorUI.h"
#include "ImGuiManager.h"

struct GameplayUpdateArgs
{
    AssetManager AssetManager;
    EditorSceneOld EditorScene;
    EditorUi EditorUI;
    ImGuiManager ImGuiManager;

    void Init()
    {
        EditorScene.Init();
        ImGuiManager.Init(AssetManager);
        EditorUI.Init();
    }
};

struct Gameplay
{
    static bool Init(GameplayUpdateArgs &args);

    static bool Update(GameplayUpdateArgs &args);

    static bool Close(GameplayUpdateArgs &args);
};
