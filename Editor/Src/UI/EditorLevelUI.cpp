//
// Created by Kamil on 16.06.2026.
//
#include "EditorLevelUI.h"

#include "AssetManager.h"
#include "imgui.h"
#include "StringUtility.hpp"
#include "misc/cpp/imgui_stdlib.h"

void EditorLevelUI::Draw(LevelManager& levels) const
{
    ImGui::Begin("Scene");

    std::string levelName = levels.Metadata[levels.Ids[levels.CurrentLevelId]];
    ImGui::InputText("##", &levelName);
    if (ImGui::IsItemDeactivatedAfterEdit() && !IsNullOrWhiteSpace(levelName))
    {
        levels.Rename(levelName);
    }

    if (ImGui::Button("Save"))
    {
        levels.Save();
    }

    ImGui::SameLine();

    if (ImGui::Button("Create New"))
    {
        levels.Create();
    }

    if (ImGui::Button("Load level"))
    {
        ImGui::OpenPopup("level_loading");
    }

    if (ImGui::BeginPopup("level_loading"))
    {
        for (const auto& [id, index] : levels.Ids)
        {
            if (ImGui::Selectable(levels.Metadata[index].c_str(), levels.CurrentLevelId == id))
            {
                levels.Load(id);
            }
        }

        ImGui::EndPopup();
    }

    ImGui::End();
}
