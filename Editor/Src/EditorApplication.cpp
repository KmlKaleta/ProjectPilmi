//
// Created by Kamil on 16.06.2026.
//
#include "EditorApplication.h"
#include "ImGui.h"

bool EditorApplication::Init()
{
    Assets.LoadAll();
    Level.Init();
    return true;
}

bool EditorApplication::Update(UndoRedoContext& ctx)
{
    if (!ImGui::GetIO().WantCaptureKeyboard)
    {
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
        {
            if (UndoRedo.CanUndo() && ImGui::IsKeyPressed(ImGuiKey_Z, true))
            {
                UndoRedo.Undo(ctx);
            }

            if (UndoRedo.CanRedo() && (ImGui::IsKeyPressed(ImGuiKey_Y, true) || (
                                           ImGui::IsKeyDown(ImGuiKey_LeftShift) &&
                                           ImGui::IsKeyPressed(ImGuiKey_Z, true))))
            {
                UndoRedo.Redo(ctx);
            }
        }

        Selection.HandleInputs(ctx.Storage, UndoRedo);
    }

    Level.Update(Assets, Selection);
    return !WindowShouldClose();
}

void EditorApplication::Close()
{
}
