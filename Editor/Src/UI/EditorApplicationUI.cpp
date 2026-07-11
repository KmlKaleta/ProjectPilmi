//
// Created by Kamil on 16.06.2026.
//
#include "EditorApplicationUI.h"

#include "../EditorApplication.h"

void EditorApplicationUI::Draw(EditorApplication& editor, UndoRedoContext& ctx) const
{
    HierarchyUI.Draw(editor.Hierarchy, editor.Selection, editor.Assets, editor.UndoRedo);
    SceneUI.Draw(editor.Assets.Levels, editor.UndoRedo);
    ComponentsUI.Draw(editor.Selection, editor.Assets, editor.UndoRedo);

    MenuUI.Draw(editor.UndoRedo, ctx);
}
