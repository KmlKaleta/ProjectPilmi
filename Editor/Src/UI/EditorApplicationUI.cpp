//
// Created by Kamil on 16.06.2026.
//
#include "EditorApplicationUI.h"

#include "../EditorApplication.h"

void EditorApplicationUI::Draw(EditorApplication& editor) const
{
    HierarchyUI.Draw(editor.Hierarchy, editor.Selection, editor.Assets);
    SceneUI.Draw();
    ComponentsUI.Draw(editor.Selection, editor.Assets);
}
