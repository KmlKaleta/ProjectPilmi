//
// Created by Kamil on 16.06.2026.
//
#include "EditorApplicationUI.h"


#include "raylib.h"

#include <cstdlib>
#include <cstring>
#include "raygui.h"
#include "style_dark.h"

void EditorApplicationUI::Init() const
{
    GuiLoadStyleDark();
}

void EditorApplicationUI::Draw()
{
    HierarchyUI.Draw();
    SceneUI.Draw();
    ComponentsUI.Draw();
}
