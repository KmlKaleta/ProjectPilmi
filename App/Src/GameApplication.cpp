//
// Created by Kamil on 28.06.2026.
//
#include "GameApplication.h"

bool GameApplication::Init()
{
    Assets.LoadAll();
    Gameplay.Init();
    return true;
}

bool GameApplication::Update()
{
    Gameplay.Update(Assets);
    return true;
}

void GameApplication::Close()
{
}