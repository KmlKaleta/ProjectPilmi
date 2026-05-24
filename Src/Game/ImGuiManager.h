#pragma once
#include "SpriteData.h"

struct GameManager;
struct AssetManager;

struct ImGuiManager
{
    bool Enable = true;

    bool ShowSprite = false;
    Vector2 SpritePosition = {};
    int SpriteIndex = {};
    int Row = {};
    int Column = {};
    Camera2D SpriteEditorCamera = {};
    float Zoom = 1;

    void Update(GameManager &gameManager, AssetManager &assetManager);

private:
    void SpriteEditorWindow(GameManager &gameManager, AssetManager &assetManager);
};
