#pragma once
#include "AssetManager.h"
#include "GameManager.h"
#include "ImGuiManager.h"

struct GameplayUpdateArgs
{
    AssetManager AssetManager;
    GameManager GameManager;
    ImGuiManager ImGuiManager;

    void Init()
    {
        GameManager.Init();
    }
};

struct Gameplay
{
    bool Init(GameplayUpdateArgs& args);

    bool Update(GameplayUpdateArgs& args);

    bool Close(GameplayUpdateArgs& args);
};
