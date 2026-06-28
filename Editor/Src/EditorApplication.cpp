//
// Created by Kamil on 16.06.2026.
//
#include "EditorApplication.h"


bool EditorApplication::Init()
{
    Assets.LoadAll();
    Level.Init();
    return true;
}

bool EditorApplication::Update()
{
    Level.Update(Assets);
    return true;
}

void EditorApplication::Close()
{
}
