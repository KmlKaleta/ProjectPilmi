//
// Created by Kamil on 26.06.2026.
//
#include "SpriteEditorApplication.h"

bool SpriteEditorApplication::Init()
{
    Window.Init();
    Scene.Init();
    return true;
}

bool SpriteEditorApplication::Update()
{
    Window.Update();
    CameraUI.Draw(Scene);
    Scene.Update(Window.Explorer, Window.Editor);
    return true;
}

void SpriteEditorApplication::Close()
{
    if (Window.Explorer.AnySelected)
        Window.Explorer.Save(Window.Explorer.Ids[Window.Explorer.Selected]);
}
