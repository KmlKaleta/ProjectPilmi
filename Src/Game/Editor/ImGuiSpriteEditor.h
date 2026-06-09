#pragma once

#include "../SpriteData.h"

struct AssetManager;
struct EditorScene;

struct ImGuiSpriteEditor
{
    Vector2 Position = {};
    int Index = {};
    int Row = {};
    int Column = {};
    Camera2D Camera = {};
    float ScaleFactor = 1;

    void AfterGame(EditorScene& editor, AssetManager& assetManager);
};
