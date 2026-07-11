//
// Created by Kamil on 05.07.2026.
//
#include "EditorMenuUI.h"
#include "../EditorUndoRedo.hpp"
#include "imgui.h"

void EditorMenuUI::Draw(EditorUndoRedo& undoRedo, UndoRedoContext& context) const
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Edit"))
        {
            // Undo button
            bool d = !undoRedo.CanUndo();
            if (d) ImGui::BeginDisabled();
            if (ImGui::MenuItem("Undo", "Ctrl+Z"))
            {
                undoRedo.Undo(context);
            }
            if (d) ImGui::EndDisabled();

            // Redo button
            d = !undoRedo.CanRedo();
            if (d) ImGui::BeginDisabled();
            if (ImGui::MenuItem("Redo", "Ctrl+Y"))
            {
                undoRedo.Redo(context);
            }
            if (d) ImGui::EndDisabled();

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
