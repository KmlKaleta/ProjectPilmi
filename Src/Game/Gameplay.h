#pragma once
#include "AssetManager.h"
#include "EditorScene.h"
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
        EditorScene.Init(AssetManager);
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
