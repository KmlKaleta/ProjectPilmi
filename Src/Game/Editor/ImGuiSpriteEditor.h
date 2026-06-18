#pragma once

#include "../SpriteData.h"

struct AssetManager;
struct EditorSceneOld;

struct ImGuiSpriteEditor
{
    Vector2 Position = {};
    int Index = {};
    int Row = {};
    int Column = {};
    Camera2D Camera = {};
    float ScaleFactor = 1;

    void AfterGame(EditorSceneOld& editor, AssetManager& assetManager);
};
