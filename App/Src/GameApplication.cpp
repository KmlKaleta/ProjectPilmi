//
// Created by Kamil on 28.06.2026.
//
#include "GameApplication.h"

bool GameApplication::Init()
{
    Assets.LoadAll();
    Gameplay.Init();
    Assets.Levels.Load(1);
    return true;
}

bool GameApplication::Update()
{
    Gameplay.Update(Assets);
    if (WindowShouldClose())
    {
        return false;
    }
    DrawFPS(10, 10);
    return true;
}

void GameApplication::Close()
{
}
