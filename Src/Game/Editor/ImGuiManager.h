#pragma once
#include "ImGuiSpriteEditor.h"

struct EditorSceneOld;
struct AssetManager;

struct ImGuiManager
{
    bool Enable = false;
    float Zoom = 1;
    ImGuiSpriteEditor SpriteEditor;
    int ActivePanel = 0;

    void AfterGame(EditorSceneOld &editor, AssetManager &assetManager);

    void Init(const AssetManager& assetManager);

    enum
    {
        PANEL_SPRITE_EDITOR = 0,

        PANEL_COUNT
    };
};
